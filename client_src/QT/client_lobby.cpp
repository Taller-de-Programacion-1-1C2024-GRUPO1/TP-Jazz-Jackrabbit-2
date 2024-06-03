#include "client_lobby.h"

#include <QMessageBox>

#include "./ui_client_lobby.h"

// ClientLobby::ClientLobby(QWidget* parent): QMainWindow(parent) ,ui(new Ui::ClientLobby) {

ClientLobby::ClientLobby(Protocol& protocol): protocol(protocol), ui(std::make_unique<Ui::ClientLobby>()) {
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
    palette.setBrush(QPalette::Window,
                     pixmap);  
    this->setPalette(palette);
}

ClientLobby::~ClientLobby() {
    // No es necesario llamar delete ui; aquí, ya que std::unique_ptr se encargará automáticamente de liberar la memoria
}

void ClientLobby::on_btnCreateMatch_clicked() {
    hide();
    
    // Selección de personaje
    CharacterSelector character_selector;
    character_selector.setModal(true);

    if (character_selector.exec() == QDialog::Accepted) {
        selected_character = character_selector.get_selected_character();
        
        // Selección de mapa
        MapSelector map_selector;
        map_selector.setModal(true);

        if (map_selector.exec() == QDialog::Accepted) {
            selected_map = map_selector.get_selected_map();
            

        }
    }
    QApplication::quit();
}

void ClientLobby::on_btnJoinMatch_clicked() {
    hide();
    
    // Selección de personaje
    CharacterSelector character_selector;
    character_selector.setModal(true);

    if (character_selector.exec() == QDialog::Accepted) {
        selected_character = character_selector.get_selected_character();    

        // seleccione una partida para unirse
        JoinMatchLobby join_match_lobby;
        join_match_lobby.setModal(true);
        if (join_match_lobby.exec() == QDialog::Accepted) {
            //selected_match = join_match_lobby.get_match_name();
        }
       
    }
    QApplication::quit();
}

void ClientLobby::on_btnQuit_clicked() {
    close();
    QApplication::quit();
}
