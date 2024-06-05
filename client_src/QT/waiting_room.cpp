#include "waiting_room.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "ui_waiting_room.h"

WaitingRoom::WaitingRoom(Queue<Command*>& q_cmds, Queue<int>& q_responses,
                         std::atomic<bool>& game_started, int& player_id, QWidget* parent):
        QDialog(parent),
        ui(new Ui::WaitingRoom),
        q_cmds(q_cmds),
        q_responses(q_responses),
        game_started(game_started),
        player_id(player_id) {
    ui->setupUi(this);


    // Establecer el fondo
    QPixmap originalPixmap(":/backgrounds/match_lobby.png");
    QSize windowSize = this->size();
    QPixmap scaledPixmap = originalPixmap.scaled(windowSize, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledPixmap);
    this->setPalette(palette);
}


WaitingRoom::~WaitingRoom() { delete ui; }

void WaitingRoom::on_pushButton_clicked() {
    std::cout << "Waiting for game to start" << std::endl;
    int player_number = q_responses.pop();
    std::cout << "Player number EN WAITING ROOM: " << player_number << std::endl;
    if (player_number < 0) {
        QMessageBox::warning(this, "Error", "error al iniciar la partida");
        return;
    }
    player_id = player_number;
    game_started = true;
    accept();
}
