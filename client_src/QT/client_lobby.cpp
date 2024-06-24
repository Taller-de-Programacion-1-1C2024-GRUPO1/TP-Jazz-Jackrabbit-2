#include "client_lobby.h"

#include "./ui_client_lobby.h"


ClientLobby::ClientLobby(Queue<std::unique_ptr<Command>>& q_cmds,
                         Queue<std::unique_ptr<QtResponse>>& q_responses, NewMapInfo& new_map_info,
                         QWidget* parent):
        QMainWindow(parent),
        ui(new Ui::ClientLobby),
        q_cmds(q_cmds),
        q_responses(q_responses),
        new_map_info(new_map_info) {
    ui->setupUi(this);
    QString fontFamily = qt_common_init(this, ":/backgrounds/lobby.png");
    QFont buttonFont(fontFamily, 24);
    ui->btnCreateMatch->setFont(buttonFont);
    ui->btnJoinMatch->setFont(buttonFont);
    ui->btnQuit->setFont(buttonFont);
}

ClientLobby::~ClientLobby() { delete ui; }

void ClientLobby::on_btnCreateMatch_clicked() {
    hide();
    CharacterSelector characterSelector;
    connect(&characterSelector, &CharacterSelector::windowClosed, this,
            &ClientLobby::handleWindowClosed);
    connect(&characterSelector, &CharacterSelector::characterSelected, this,
            &ClientLobby::handleCharacterSelected);

    if (characterSelector.exec() == QDialog::Accepted) {
        MapSelector map_selector(q_cmds, q_responses, selected_character, new_map_info,
                                 player_name);
        connect(&map_selector, &MapSelector::windowClosed, this, &ClientLobby::handleWindowClosed);
        int result = map_selector.exec();
        if (result == QDialog::Accepted) {
            QApplication::exit(OK);
        } else if (result == OK_MAP_CREATOR) {
            QApplication::exit(OK_MAP_CREATOR);
        } else if (result == EDIT_MAP) {
            QApplication::exit(EDIT_MAP);
        } else if (result == CLOSE_MAP_CREATOR) {
            QApplication::exit(ERROR);
        } else {
            std::cerr << "Error creating match, map_selector failed" << std::endl;
            QApplication::exit(ERROR);
        }
    } else {
        std::cerr << "Error creating match, characterSelector failed" << std::endl;
        QApplication::exit(ERROR);
    }
}

void ClientLobby::on_btnJoinMatch_clicked() {
    hide();
    CharacterSelector characterSelector;
    connect(&characterSelector, &CharacterSelector::characterSelected, this,
            &ClientLobby::handleCharacterSelected);
    connect(&characterSelector, &CharacterSelector::windowClosed, this,
            &ClientLobby::handleWindowClosed);

    if (characterSelector.exec() == QDialog::Accepted) {
        JoinMatchLobby joinMatchLobby(q_cmds, q_responses, selected_character, player_name);
        connect(&joinMatchLobby, &JoinMatchLobby::windowClosed, this,
                &ClientLobby::handleWindowClosed);
        if (joinMatchLobby.exec() == QDialog::Accepted) {
            QApplication::exit(OK);
        } else {
            std::cerr << "Failed to join game, joinMatchLobby failed" << std::endl;
            QApplication::exit(ERROR);
        }
    } else {
        std::cerr << "Failed to join game, character selector failed" << std::endl;
        QApplication::exit(ERROR);
    }
}

void ClientLobby::on_btnQuit_clicked() { QApplication::exit(ERROR); }


void ClientLobby::handleCharacterSelected(ChampionType character,
                                          const std::string& selected_player_name) {
    selected_character = character;
    player_name = selected_player_name;
}


void ClientLobby::handleWindowClosed() { QApplication::exit(ERROR); }


void ClientLobby::closeEvent(QCloseEvent* event) {
    qDebug() << "Window is closing";
    handleWindowClosed();
    QMainWindow::closeEvent(event);
}
