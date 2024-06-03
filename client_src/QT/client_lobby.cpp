#include "client_lobby.h"

#include "./ui_client_lobby.h"


ClientLobby::ClientLobby(Queue<Command*>& q_cmds, QWidget* parent):
        QMainWindow(parent), ui(new Ui::ClientLobby), q_cmds(q_cmds) {
    ui->setupUi(this);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/04B_30__.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(fontFamily);
        QApplication::setFont(font);
        QFont buttonFont(fontFamily, 24);
        ui->btnCreateMatch->setFont(buttonFont);
        ui->btnJoinMatch->setFont(buttonFont);
        ui->btnQuit->setFont(buttonFont);
    } else {
        qWarning() << "No se pudo cargar la fuente 04B_30__";
    }
    QPixmap pixmap(":/backgrounds/lobby.png");
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);
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
        MapSelector map_selector(q_cmds, selected_character);
        connect(&map_selector, &MapSelector::windowClosed, this, &ClientLobby::handleWindowClosed);
        if (map_selector.exec() == QDialog::Accepted) {
            // ENVIO COMANDO E INICIO PARTIDA
            QApplication::exit(0);
        }
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
        JoinMatchLobby joinMatchLobby(q_cmds, selected_character);
        connect(&joinMatchLobby, &JoinMatchLobby::windowClosed, this,
                &ClientLobby::handleWindowClosed);

        if (joinMatchLobby.exec() == QDialog::Accepted) {

            // ESpero a que se conecten todos los jugadores y se inicie la partida


            QApplication::exit(0);
        }
    }
}

void ClientLobby::on_btnQuit_clicked() { QApplication::exit(1); }


void ClientLobby::handleCharacterSelected(ChampionType character) {
    selected_character = character;
}


void ClientLobby::handleWindowClosed() { QApplication::exit(1); }
