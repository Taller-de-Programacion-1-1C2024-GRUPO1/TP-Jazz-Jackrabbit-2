#include "map_editor_lobby.h"

#include "ui_map_editor_lobby.h"

MapEditorLobby::MapEditorLobby(Queue<std::unique_ptr<Command>>& q_cmds,
                               Queue<std::unique_ptr<QtResponse>>& q_responses,
                               std::string& selected_map, NewMapInfo& new_map_info, QWidget* parent):

        QDialog(parent),
        ui(new Ui::MapEditorLobby),
        q_cmds(q_cmds),
        q_responses(q_responses),
        selected_map(selected_map),
        new_map_info(new_map_info) {
    ui->setupUi(this);
    QPixmap pixmap(":/backgrounds/match_lobby.png");
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);
}

MapEditorLobby::~MapEditorLobby() { delete ui; }


void MapEditorLobby::on_btnRefresh_clicked() {
    try {
        q_cmds.push(std::make_unique<MatchCommand>(REFRESH, 0, "", "", NULL_CHAMPION_TYPE));
        bool could_pop = false;
        std::unique_ptr<QtResponse> response;
        while (!could_pop) {
            could_pop = q_responses.try_pop(response);
        }
        if (response->get_info_type() == REFRESH) {
            std::vector<std::string> maps = response->get_maps_available();
            if (maps.empty()) {
                QMessageBox::warning(this, "Error", "No hay partidas disponibles");
                return;
            }
            ui->comboBoxMaps->clear();
            for (const std::string& map: maps) {
                std::cout << "Maps: " << map << std::endl;
                ui->comboBoxMaps->addItem(QString::fromStdString(map));
            }

        } else {
            QMessageBox::warning(this, "Error", "RECIBI UNA RESPUESTA QUE NO DEBERIA RECIBIR");
        }
    } catch (const ClosedQueue& e) {
        QMessageBox::warning(this, "Error", "Se cerró la cola de respuestas o la cola de comandos");
        reject();

    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", "No se pudo conectar con el servidor");
        reject();
    }
}


void MapEditorLobby::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}


void MapEditorLobby::on_btnEdit_clicked() {
    std::string map_name = ui->comboBoxMaps->currentText().toStdString();
    if (map_name.empty()) {
        QMessageBox::warning(this, "Error", "Please select a map.");
        return;
    }
    selected_map = map_name;
    new_map_info = NewMapInfo(map_name, 0, 0, 0, 0);
    done(EDIT_MAP);
}


void MapEditorLobby::on_btnPlay_clicked() {
    std::string map_name = ui->comboBoxMaps->currentText().toStdString();
    if (map_name.empty()) {
        QMessageBox::warning(this, "Error", "Please select a map.");
        return;
    }
    selected_map = map_name;
    done(PLAY_MAP);
}
