#include "client_lobby.h"

#include <QMessageBox>

#include "./ui_client_lobby.h"
ClientLobby::ClientLobby(QWidget* parent): QMainWindow(parent), ui(new Ui::ClientLobby) {
    ui->setupUi(this);
}

ClientLobby::~ClientLobby() { delete ui; }

int first_number, seccond_number, result;


int create_match_code;
void ClientLobby::on_btnCreate_clicked() {
    create_match_code = ui->txtCreateMatchCode->toPlainText().toInt();

    ui->txtAvailableMatches->setPlainText(QString::number(create_match_code));
}

int join_match_code;
void ClientLobby::on_btnJoin_clicked() {
    join_match_code = ui->txtJoinMatchCode->toPlainText().toInt();
}

void ClientLobby::on_btnError_clicked() {
    // QMessageBox::about(this, "ERROR", "Ingrese un numero valido");
    QMessageBox::critical(this, "ERROR", "Ingrese un numero valido");
}
