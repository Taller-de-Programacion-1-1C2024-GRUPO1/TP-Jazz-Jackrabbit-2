#include "map_selector.h"

#include "ui_map_selector.h"


MapSelector::MapSelector(QWidget* parent): QDialog(parent), ui(new Ui::MapSelector) {
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

QString MapSelector::get_selected_map() const {
    return selected_map;
}

void MapSelector::on_btnMap1_clicked() {
    selected_map = "Map1";
    accept(); 
}


void MapSelector::on_btnMap2_clicked() {
    selected_map = "Map2";
    accept(); 

}


void MapSelector::on_btnMapCreate_clicked() {
    selected_map = "MapCreate";
    accept(); 
}


