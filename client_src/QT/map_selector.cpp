#include "map_selector.h"

#include "ui_map_selector.h"


MapSelector::MapSelector(Queue<Command*>& q_cmds, Queue<int>& q_responses,
                         std::atomic<bool>& game_started, ChampionType selected_character,
                         int& player_id, QWidget* parent):
        QDialog(parent),
        ui(new Ui::MapSelector),
        q_cmds(q_cmds),
        q_responses(q_responses),
        player_id(player_id),
        game_started(game_started),
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
    selected_map = "carrotus";  /////////////////PONER NOMBRE
    start_match();
}


void MapSelector::on_btnMap2_clicked() {
    selected_map = "carrotus";
    start_match();
}


void MapSelector::on_btnMapCreate_clicked() {
    selected_map = "carrotus";  /////////////////PONER NOMBRE
    start_match();
}

void MapSelector::start_match() {
    int number_of_players = ui->spinNumberOfPlayers->value();
    std::string match_name = ui->txtMatchName->toPlainText().toStdString();
    if (match_name.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a match name.");
        return;
    }

    /*
    MatchCommand(int type, int number_players, const std::string& match_name,
                 const std::string& map_name, ChampionType character_name);
    */

    // enum match_type {
    //     NEW_MATCH = 0,
    //     JOIN,
    //     REFRESH,
    // };


    // ENVIO COMANDO preguntando por existencia de nombre de partida.
    // Si no existe acepto para que inicie la partida

    MatchCommand cmd = MatchCommand(NEW_MATCH, number_of_players, match_name, selected_map,
                                    selected_character);
    q_cmds.push(&cmd);

    /*
    int response;
    bool could_pop = false;
    while (!could_pop) {
        could_pop = q_responses.try_pop(response);
        QMessageBox::warning(this, "Error", "trying to connect:");
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    */
    int response = q_responses.pop();
    if (response == 0) {
        hide();
        WaitingRoom waiting_room(q_cmds, q_responses, game_started, player_id);
        if (waiting_room.exec() == QDialog::Accepted) {
            accept();
        } else {
            // error ?
        }
    } else if (response == -1) {
        // no pude conectarme
        QMessageBox::warning(this, "Error", "Match name already exists.");
        return;
    } else {
        QMessageBox::warning(this, "Error", "RECIBI UNA RESPUESTA QUE NO DEBERIA RECIBIR");
        return;
    }
}


void MapSelector::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}
