#include "match_lobby.h"

#include "ui_match_lobby.h"

#include <QDebug>
#include <QFontDatabase>
#include <QMessageBox>

MatchLobby::MatchLobby(QWidget* parent): QDialog(parent), map(""), ui(new Ui::MatchLobby) {
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

void MatchLobby::on_btnMap1_clicked()
{
    map = "mapa1";
}


void MatchLobby::on_btnMap2_clicked()
{
    map = "mapa2";
}


void MatchLobby::on_btnMapCreate_clicked()
{
    map = "create_a_map";
}


void MatchLobby::on_btnContinue_clicked()
{
    if (map == "") {
            QMessageBox::critical(this, "ERROR", "Seleccione un mapa");
    }
    else  if  (map == "create_a_map") {
         QMessageBox::critical(this, "SDL Turn", "crea un mapa");
        QApplication::quit(); // Cierra la aplicación
    }
    else {
        QMessageBox::critical(this, "SDL Turn", "empieza el juego");
        QApplication::quit(); // Cierra la aplicación
    }
}

