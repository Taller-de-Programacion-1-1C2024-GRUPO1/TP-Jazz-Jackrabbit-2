#include "client_lobby.h"

#include "./ui_client_lobby.h"


ClientLobby::ClientLobby(QWidget* parent): QMainWindow(parent), ui(new Ui::ClientLobby) {
    ui->setupUi(this);
}

ClientLobby::~ClientLobby() { delete ui; }
