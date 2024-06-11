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
        MapSelector map_selector(q_cmds, q_responses, selected_character, new_map_info);
        connect(&map_selector, &MapSelector::windowClosed, this, &ClientLobby::handleWindowClosed);
        int result = map_selector.exec();
        if (result == QDialog::Accepted) {
            QApplication::exit(OK);
        } else if (result == OK_MAP_CREATOR) {
            QApplication::exit(OK_MAP_CREATOR);
        } else if (result == CLOSE_MAP_CREATOR) {
            std::cout << "Cerrando QT..." << std::endl;
            QApplication::exit(ERROR);
        } else {
            std::cerr << "Error al crear partida, map_selector falló" << std::endl;
            QApplication::exit(ERROR);
        }
    } else {
        std::cerr << "Error al crear partida, characterSelector falló" << std::endl;
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
        JoinMatchLobby joinMatchLobby(q_cmds, q_responses, selected_character);
        connect(&joinMatchLobby, &JoinMatchLobby::windowClosed, this,
                &ClientLobby::handleWindowClosed);
        if (joinMatchLobby.exec() == QDialog::Accepted) {
            QApplication::exit(OK);
        } else {
            std::cerr << "Error al unirse a partida, joinMatchLobby room falló" << std::endl;
            QApplication::exit(ERROR);
        }
    } else {
        std::cerr << "Error al unirse a partida, character selector falló" << std::endl;
        QApplication::exit(ERROR);
    }
}

void ClientLobby::on_btnQuit_clicked() { QApplication::exit(ERROR); }


void ClientLobby::handleCharacterSelected(ChampionType character) {
    selected_character = character;
}


void ClientLobby::handleWindowClosed() { QApplication::exit(ERROR); }


void ClientLobby::closeEvent(QCloseEvent* event) {
    qDebug() << "Window is closing";
    handleWindowClosed();
    QMainWindow::closeEvent(event);
}
