#include "match_lobby.h"

#include "ui_match_lobby.h"

MatchLobby::MatchLobby(QWidget* parent): QDialog(parent), ui(new Ui::MatchLobby) {
    ui->setupUi(this);
    // Establecer el fondo
    QPixmap originalPixmap(":/backgrounds/match_lobby.png");
    QSize windowSize = this->size();
    QPixmap scaledPixmap = originalPixmap.scaled(windowSize, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledPixmap);
    this->setPalette(palette);
}

MatchLobby::~MatchLobby() { delete ui; }


void MatchLobby::on_btnStart_clicked() {
    QMessageBox::critical(this, "SDL Turn", "empieza el juego");
    QApplication::quit();  // Cierra la aplicación
}
