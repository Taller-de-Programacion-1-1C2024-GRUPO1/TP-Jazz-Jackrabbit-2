#include "map_selector.h"

#include "ui_map_selector.h"

MapSelector::MapSelector(Queue<std::unique_ptr<Command>>& q_cmds,
                         Queue<std::unique_ptr<QtResponse>>& q_responses,
                         ChampionType selected_character, NewMapInfo& new_map_info,
                         int& map_texture, QWidget* parent):
        QDialog(parent),
        ui(new Ui::MapSelector),
        q_cmds(q_cmds),
        q_responses(q_responses),
        selected_character(selected_character),
        new_map_info(new_map_info),
        map_texture(map_texture) {
    ui->setupUi(this);

    // Set the background
    QPixmap originalPixmap(":/backgrounds/match_lobby.png");
    QSize windowSize = this->size();
    QPixmap scaledPixmap = originalPixmap.scaled(windowSize, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledPixmap);
    this->setPalette(palette);
}

MapSelector::~MapSelector() { delete ui; }

void MapSelector::on_btnMap1_clicked() {
    selected_map = DEFAULT_MAP_CARROTUS;  // CASTLE //
    map_texture = CASTLE;
    start_match();
}

void MapSelector::on_btnMap2_clicked() {
    selected_map = DEFAULT_MAP_CARROTUS;
    map_texture = CARROTUS;
    start_match();
}

void MapSelector::on_btnMapCreate_clicked() {
    hide();
    MapCreatorLobby map_creator_lobby(new_map_info);
    connect(&map_creator_lobby, &MapCreatorLobby::windowClosed, this,
            &MapSelector::handleWindowClosed);

    int result = map_creator_lobby.exec();
    if (result == QDialog::Accepted) {
        // QApplication::exit(OK_MAP_CREATOR);
        this->done(OK_MAP_CREATOR);
    } else {
        this->done(CLOSE_MAP_CREATOR);
    }
}

void MapSelector::handleWindowClosed() { QApplication::exit(ERROR); }

void MapSelector::start_match() {
    int number_of_players = ui->spinNumberOfPlayers->value();
    std::string match_name = ui->txtMatchName->toPlainText().toStdString();
    if (match_name.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a match name.");
        return;
    }

    try {
        std::cout << "enviando comando" << std::endl;
        q_cmds.push(std::make_unique<MatchCommand>(NEW_MATCH, number_of_players, match_name,
                                                   selected_map, selected_character));


        bool could_pop = false;
        std::unique_ptr<QtResponse> response;
        while (!could_pop) {
            could_pop = q_responses.try_pop(response);
        }
        std::cout << "Response en MAP SELECTOR: " << response->get_response() << std::endl;
        if (response->get_response() == OK) {
            hide();
            WaitingRoom waiting_room(q_cmds, q_responses);
            if (waiting_room.exec() == QDialog::Accepted) {
                this->done(QDialog::Accepted);
            } else {
                std::cerr << "Error en waiting room" << std::endl;
                this->done(ERROR);
            }
        } else if (response->get_response() == ERROR) {
            // Couldn't connect
            QMessageBox::warning(this, "Error", "Match name already exists.");
            this->done(ERROR);
        } else {
            QMessageBox::warning(this, "Error", "Received an unexpected response.");
            this->done(ERROR);
        }
    } catch (const ClosedQueue& e) {
        QMessageBox::warning(this, "Error", "Se cerró la cola de respuestas o la cola de comandos");
        reject();

    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", "No se pudo conectar con el servidor");
        reject();
    }
}

void MapSelector::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}

void MapSelector::on_btnCustomMaps_clicked() {
    std::string match_name = ui->txtMatchName->toPlainText().toStdString();
    if (match_name.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a match name.");
        return;
    }
    hide();
    MapEditorLobby map_editor_lobby(q_cmds, q_responses, selected_map);
    connect(&map_editor_lobby, &MapEditorLobby::windowClosed, this,
            &MapSelector::handleWindowClosed);

    int result = map_editor_lobby.exec();
    if (result == PLAY_MAP) {
        start_match();
    } else if (result == EDIT_MAP) {
        this->done(EDIT_MAP);
    } else {
        this->done(CLOSE_MAP_CREATOR);
    }
}
