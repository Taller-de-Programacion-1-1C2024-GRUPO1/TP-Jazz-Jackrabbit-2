#include "client_lobby.h"

#include <QMessageBox>

#include "./ui_client_lobby.h"

// ClientLobby::ClientLobby(QWidget* parent): QMainWindow(parent) ,ui(new Ui::ClientLobby) {

ClientLobby::ClientLobby(Protocol& protocol): protocol(protocol), ui(new Ui::ClientLobby) {
    ui->setupUi(this);

    // Cargar la fuente desde los recursos
    int fontId = QFontDatabase::addApplicationFont(":/fonts/04B_30__.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(fontFamily);
        QApplication::setFont(font);
    } else {
        qWarning() << "No se pudo cargar la fuente 04B_30__";
    }

    // Establecer el fondo
    // background-image: url(:/backgrounds/lobby.png)
    QPixmap pixmap(":/backgrounds/lobby.png");
    QPalette palette;
    palette.setBrush(QPalette::Window,
                     pixmap);  // Usar QPalette::Window en lugar de QPalette::Background
    this->setPalette(palette);
}

ClientLobby::~ClientLobby() { delete ui; }

int match_code;
// std::string map;
void ClientLobby::on_btnCreateMatch_clicked() {
    match_code = ui->txtCreateMatch->toPlainText().toInt();
    // map = "mapa1";
    // Match match(NEW_MATCH, std::to_string(match_code), map);
    // protocol.send(match);

    if (match_code == 0) {
        QMessageBox::critical(this, "ERROR", "nombre de partida invalido");
        return;
    }

    hide();
    MapSelector map_selector;
    map_selector.setModal(true);
    map_selector.exec();

    // ui->txtAvailableMatches->setPlainText(QString::number(match_code));
}

int join_match_code;
void ClientLobby::on_btnJoinMatch_clicked() {
    join_match_code = ui->txtJoinMatch->toPlainText().toInt();
}


void ClientLobby::on_btnError_clicked() {
    // QMessageBox::about(this, "ERROR", "Ingrese un numero valido");
    QMessageBox::critical(this, "ERROR", "Ingrese un numero valido");
}

/*
void ClientLobby::run(int argc, char* argv[])
{
   QApplication a(argc, argv);
   Q_INIT_RESOURCE(resources);
   ClientLobby w;
   w.show();
   a.exec();
}
*/
