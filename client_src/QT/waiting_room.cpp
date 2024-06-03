#include "waiting_room.h"

#include "ui_waiting_room.h"

#include <iostream>
#include <thread>
#include <chrono>

WaitingRoom::WaitingRoom(ClientSender& sender, ClientReceiver& receiver, QWidget* parent): 
    QDialog(parent), ui(new Ui::WaitingRoom), sender(sender), receiver(receiver) {
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

void WaitingRoom::on_pushButton_clicked()
{
     // aca en realidad le pregunto al protocolo si ya puedo iniciar la partida

    accept();
}

