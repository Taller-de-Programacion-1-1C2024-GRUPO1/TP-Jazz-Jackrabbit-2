#include "waiting_room.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "ui_waiting_room.h"

WaitingRoom::WaitingRoom(Queue<std::unique_ptr<Command>>& q_cmds,
                         Queue<std::unique_ptr<QtResponse>>& q_responses, QWidget* parent):
        QDialog(parent),
        ui(new Ui::WaitingRoom),
        q_cmds(q_cmds),
        q_responses(q_responses),
        stop_thread(false) {
    ui->setupUi(this);

    // Establecer el fondo
    QPixmap originalPixmap(":/backgrounds/match_lobby.png");
    QSize windowSize = this->size();
    QPixmap scaledPixmap = originalPixmap.scaled(windowSize, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledPixmap);
    this->setPalette(palette);

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
        std::cout << "Waiting for game to start" << std::endl;
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

            std::cout << "Player number EN WAITING ROOM: " << player_number->get_response()
                      << std::endl;
            if (player_number->get_response() < 0) {
                QMetaObject::invokeMethod(this, [this]() {
                    QMessageBox::warning(this, "Error", "error al iniciar la partida");
                });
                return;
            }
            QMetaObject::invokeMethod(this, [this]() { accept(); });

        } catch (const ClosedQueue& e) {
            QMetaObject::invokeMethod(
                    this,
                    [this]() {
                        QMessageBox::warning(
                                this, "Error",
                                "Se cerró la cola de respuestas o la cola de comandos");
                        reject();
                    },
                    Qt::QueuedConnection);

        } catch (const std::exception& e) {
            QMetaObject::invokeMethod(
                    this,
                    [this]() {
                        QMessageBox::warning(this, "Error", "No se pudo conectar con el servidor");
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
