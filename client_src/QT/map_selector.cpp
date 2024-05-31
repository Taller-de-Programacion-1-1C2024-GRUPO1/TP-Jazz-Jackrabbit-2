#include "map_selector.h"

#include "ui_map_selector.h"


MapSelector::MapSelector(QWidget* parent): QDialog(parent), map(""), ui(new Ui::MapSelector) {
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

void MapSelector::on_btnMap1_clicked() { map = "mapa1"; }


void MapSelector::on_btnMap2_clicked() { map = "mapa2"; }


void MapSelector::on_btnMapCreate_clicked() { map = "create_a_map"; }


void MapSelector::on_btnContinue_clicked() {
    if (map == "") {
        QMessageBox::critical(this, "ERROR", "Seleccione un mapa");
    } else if (map == "create_a_map") {
        QMessageBox::critical(this, "SDL Turn", "crea un mapa");
        QApplication::quit();  // Cierra la aplicación
    } else {
        hide();
        MatchLobby match_lobby;
        match_lobby.setModal(true);
        match_lobby.exec();
    }
}
