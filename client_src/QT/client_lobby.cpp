#include "client_lobby.h"

#include "./ui_client_lobby.h"

ClientLobby::ClientLobby(QWidget* parent): QMainWindow(parent), ui(new Ui::ClientLobby) {
    ui->setupUi(this);
}

ClientLobby::~ClientLobby() { delete ui; }

int first_number, seccond_number, result;

void ClientLobby::on_btnPlus_clicked() {
    first_number = ui->txtFirstNumber->toPlainText().toInt();
    seccond_number = ui->txtSeccondNumber->toPlainText().toInt();
    result = first_number + seccond_number;
    ui->txtResult->setPlainText(QString::number(result));
}
