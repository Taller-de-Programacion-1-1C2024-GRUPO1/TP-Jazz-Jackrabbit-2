#include "join_match_lobby.h"

#include <chrono>
#include <thread>

#include "ui_join_match_lobby.h"


JoinMatchLobby::JoinMatchLobby(Queue<std::shared_ptr<Command>>& q_cmds, Queue<int>& q_responses,
                               std::atomic<bool>& game_started, ChampionType selected_character,
                               int& player_id, QWidget* parent):
        QDialog(parent),
        ui(new Ui::JoinMatchLobby),
        q_cmds(q_cmds),
        q_responses(q_responses),
        player_id(player_id),
        game_started(game_started),
        selected_character(selected_character) {
    ui->setupUi(this);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/04B_30__.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(fontFamily);
        QApplication::setFont(font);
    } else {
        qWarning() << "No se pudo cargar la fuente 04B_30__";
    }
    QPixmap pixmap(":/backgrounds/match_lobby.png");
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);
}

JoinMatchLobby::~JoinMatchLobby() { delete ui; }


void JoinMatchLobby::on_btnJoin_clicked() {
    std::string match_name = ui->txtMatchName->toPlainText().toStdString();


    // MatchCommand(int type, int number_players, const std::string& match_name,
    //                         const std::string& map_name):

    // enum match_type {
    //     NEW_MATCH = 0,
    //     JOIN,
    //     REFRESH,
    // };


    // ENVIO COMANDO preguntando por existencia de partida. Si existe acepto para que inicie la
    // partida


    MatchCommand cmd = MatchCommand(JOIN, 0, match_name, "", selected_character);
    q_cmds.push(std::make_shared<MatchCommand>(cmd));

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

void JoinMatchLobby::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}
