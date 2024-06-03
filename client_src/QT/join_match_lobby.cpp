#include "join_match_lobby.h"

#include "ui_join_match_lobby.h"

JoinMatchLobby::JoinMatchLobby(QWidget* parent): QDialog(parent), ui(new Ui::JoinMatchLobby) {
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
    palette.setBrush(QPalette::Window,
                     pixmap);  
    this->setPalette(palette);

}

JoinMatchLobby::~JoinMatchLobby() { delete ui; }



QString JoinMatchLobby::get_match_name() const {
    return match_name;
}


void JoinMatchLobby::on_btnJoin_clicked()
{
    match_name = ui->txtMatchName->toPlainText();
    accept();
}

