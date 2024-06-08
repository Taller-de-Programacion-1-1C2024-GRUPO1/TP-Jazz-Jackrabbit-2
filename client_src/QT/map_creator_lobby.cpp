#include "map_creator_lobby.h"

#include "ui_map_creator_lobby.h"

MapCreatorLobby::MapCreatorLobby(QWidget* parent): QDialog(parent), ui(new Ui::MapCreatorLobby) {
    ui->setupUi(this);
    // Establecer el fondo
    QPixmap originalPixmap(":/backgrounds/match_lobby.png");
    QSize windowSize = this->size();
    QPixmap scaledPixmap = originalPixmap.scaled(windowSize, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledPixmap);
    this->setPalette(palette);
}

MapCreatorLobby::~MapCreatorLobby() { delete ui; }


void MapCreatorLobby::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}

void MapCreatorLobby::on_btnTexture1_clicked() {
    start_creating_map(1);  // ACA SELECCIONO LA TEXTURA
}


void MapCreatorLobby::on_btnTexture2_clicked() {
    start_creating_map(2);  // ACA SELECCIONO LA TEXTURA
}


void MapCreatorLobby::on_btnTexture3_clicked() {
    start_creating_map(3);  // ACA SELECCIONO LA TEXTURA
}


void MapCreatorLobby::start_creating_map(int texture) {
    std::string map_name = ui->txtMapName->toPlainText().toStdString();
    if (map_name.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a map name.");
        return;
    }
    int width = ui->spinWidth->value();
    int height = ui->spinHeight->value();
    QApplication::exit(-2);
}
