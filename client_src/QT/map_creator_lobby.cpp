#include "map_creator_lobby.h"

#include "ui_map_creator_lobby.h"

MapCreatorLobby::MapCreatorLobby(NewMapInfo& new_map_info, QWidget* parent):
        QDialog(parent), new_map_info(new_map_info), ui(new Ui::MapCreatorLobby) {
    ui->setupUi(this);
    qt_common_init(this, ":/backgrounds/match_lobby.png");
}

MapCreatorLobby::~MapCreatorLobby() { delete ui; }


void MapCreatorLobby::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}

void MapCreatorLobby::on_btnTexture1_clicked() { start_creating_map(JUNGLE); }


void MapCreatorLobby::on_btnTexture2_clicked() { start_creating_map(CARROTUS); }


void MapCreatorLobby::start_creating_map(int texture) {
    std::string map_name = ui->txtMapName->toPlainText().toStdString();
    if (map_name.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a map name.");
        return;
    }
    int width = ui->spinWidth->value();
    int height = ui->spinHeight->value();
    int max_players = ui->spinMaxPlayers->value();
    new_map_info = NewMapInfo(map_name, width, height, texture, max_players);
    accept();
}
