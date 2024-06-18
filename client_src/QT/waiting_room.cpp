#include "waiting_room.h"

#include "ui_waiting_room.h"

WaitingRoom::WaitingRoom(Queue<std::unique_ptr<Command>>& q_cmds,
                         Queue<std::unique_ptr<QtResponse>>& q_responses, QWidget* parent):
        QDialog(parent),
        ui(new Ui::WaitingRoom),
        q_cmds(q_cmds),
        q_responses(q_responses),
        stop_thread(false) {
    ui->setupUi(this);
    qt_common_init(this, ":/backgrounds/match_lobby.png");

    // Inicia el hilo para esperar la respuesta
    startWaitingForGame();
}

WaitingRoom::~WaitingRoom() {
    stopWaitingForGame();
    if (waiting_thread.joinable()) {
        waiting_thread.join();
    }
    delete ui;
}

void WaitingRoom::startWaitingForGame() {
    waiting_thread = std::thread([this]() {
        std::unique_ptr<QtResponse> player_number;
        try {
            while (!stop_thread) {
                bool could_pop = q_responses.try_pop(player_number);
                if (could_pop) {
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            if (stop_thread)
                return;
            if (player_number->get_response() < 0) {
                QMetaObject::invokeMethod(this, [this]() {
                    QMessageBox::warning(this, "WaitingRoom Error: ", "Error starting the match");
                });
                return;
            }
            QMetaObject::invokeMethod(this, [this]() { accept(); });

        } catch (const ClosedQueue& e) {
            QMetaObject::invokeMethod(
                    this,
                    [this]() {
                        QMessageBox::warning(this, "WaitingRoom Error: ",
                                             "The response queue or command queue was closed");
                        reject();
                    },
                    Qt::QueuedConnection);

        } catch (const std::exception& e) {
            QMetaObject::invokeMethod(
                    this,
                    [this]() {
                        QMessageBox::warning(
                                this, "WaitingRoom Error: ", "Could not connect to the server");
                        reject();
                    },
                    Qt::QueuedConnection);
        }
    });
}

void WaitingRoom::stopWaitingForGame() { stop_thread = true; }

void WaitingRoom::closeEvent(QCloseEvent* event) {
    stopWaitingForGame();
    if (waiting_thread.joinable()) {
        waiting_thread.join();
    }
    QDialog::closeEvent(event);
}
