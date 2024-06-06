#include "waiting_room.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "ui_waiting_room.h"

WaitingRoom::WaitingRoom(std::shared_ptr<Queue<std::shared_ptr<Command>>>& q_cmds, std::shared_ptr<Queue<int>> q_responses,
                         std::atomic<bool>& game_started, int& player_id, QWidget* parent):
        QDialog(parent),
        ui(new Ui::WaitingRoom),
        q_cmds(q_cmds),
        q_responses(q_responses),
        game_started(game_started),
        player_id(player_id),
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
        bool could_pop = false;
        int player_number;
        while (!stop_thread && !could_pop) {
            could_pop = q_responses->try_pop(player_number);
            if (!could_pop) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Espera de 100 ms
            }
        }
        if (stop_thread) return;

        std::cout << "Player number EN WAITING ROOM: " << player_number << std::endl;
        if (player_number < 0) {
            QMetaObject::invokeMethod(this, [this]() {
                QMessageBox::warning(this, "Error", "error al iniciar la partida");
            });
            return;
        }
        player_id = player_number;
        game_started = true;
        QMetaObject::invokeMethod(this, [this]() {
            accept();
        });
    });
}

void WaitingRoom::stopWaitingForGame() {
    stop_thread = true;
}

void WaitingRoom::closeEvent(QCloseEvent* event) {
    stopWaitingForGame();
    if (waiting_thread.joinable()) {
        waiting_thread.join();
    }
    QDialog::closeEvent(event);
}
