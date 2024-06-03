#include "map_selector.h"

#include "ui_map_selector.h"


MapSelector::MapSelector(ClientSender& sender,  ClientReceiver& receiver, const std::string& selected_character,
                         QWidget* parent):
        QDialog(parent),
        ui(new Ui::MapSelector),
        sender(sender),
        receiver(receiver),
        selected_character(selected_character) {
    ui->setupUi(this);

    // Establecer el fondo
    QPixmap originalPixmap(":/backgrounds/match_lobby.png");
    QSize windowSize = this->size();
    QPixmap scaledPixmap = originalPixmap.scaled(windowSize, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledPixmap);
    this->setPalette(palette);
}
MapSelector::~MapSelector() { delete ui; }


void MapSelector::on_btnMap1_clicked() {
    selected_map = "map1";
    start_match();
}


void MapSelector::on_btnMap2_clicked() {
    selected_map = "map2";
    start_match();
}


void MapSelector::on_btnMapCreate_clicked() {
    selected_map = "create_map";
    start_match();
}

void MapSelector::start_match() {
    int number_of_players = ui->spinNumberOfPlayers->value();
    std::string match_name = ui->txtMatchName->toPlainText().toStdString();
    if (match_name.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a match name.");
        return;
    }


    // MatchCommand(int type, int number_players, const std::string& match_name,
    //                        const std::string& map_name):

    // enum match_type {
    //     NEW_MATCH = 0,
    //     JOIN,
    //     REFRESH,
    // };


    // ENVIO COMANDO preguntando por existencia de nombre de partida.
    // Si no existe acepto para que inicie la partida

    MatchCommand cmd = MatchCommand(NEW_MATCH, number_of_players, selected_character, selected_map);

    //sender.sendCommand(&cmd);

    //receiver.receiveCommand(); 
    


    hide();
    WaitingRoom waiting_room(sender, receiver);
    if (waiting_room.exec() == QDialog::Accepted) {
        accept();
    } else {
        // error ?
    }
}


void MapSelector::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}
