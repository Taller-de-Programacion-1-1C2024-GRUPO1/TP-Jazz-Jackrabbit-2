#include "map_selector.h"

#include "ui_map_selector.h"

MapSelector::MapSelector(Queue<std::unique_ptr<Command>>& q_cmds,
                         Queue<std::unique_ptr<QtResponse>>& q_responses,
                         ChampionType selected_character, NewMapInfo& new_map_info,
                         const std::string& player_name, QWidget* parent):
        QDialog(parent),
        ui(new Ui::MapSelector),
        q_cmds(q_cmds),
        q_responses(q_responses),
        selected_character(selected_character),
        new_map_info(new_map_info),
        player_name(player_name) {
    ui->setupUi(this);
    qt_common_init(this, ":/backgrounds/match_lobby.png");
}

MapSelector::~MapSelector() { delete ui; }

void MapSelector::on_btnMap1_clicked() {
    selected_map = DEFAULT_MAP_JUNGLE;
    start_match();
}

void MapSelector::on_btnMap2_clicked() {
    selected_map = DEFAULT_MAP_CARROTUS;
    start_match();
}

void MapSelector::on_btnMapCreate_clicked() {
    hide();
    MapCreatorLobby map_creator_lobby(new_map_info);
    connect(&map_creator_lobby, &MapCreatorLobby::windowClosed, this,
            &MapSelector::handleWindowClosed);

    int result = map_creator_lobby.exec();
    if (result == QDialog::Accepted) {
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

        q_cmds.push(std::make_unique<MatchCommand>(NEW_MATCH, number_of_players, match_name,
                                                   selected_map, selected_character, player_name));

        bool could_pop = false;
        std::unique_ptr<QtResponse> response;
        while (!could_pop) {
            could_pop = q_responses.try_pop(response);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        if (response->get_response() == OK) {
            hide();
            WaitingRoom waiting_room(q_cmds, q_responses);
            if (waiting_room.exec() == QDialog::Accepted) {
                this->done(QDialog::Accepted);
            } else {
                std::cerr << "Error in waiting room" << std::endl;
                this->done(ERROR);
            }
        } else if (response->get_response() == ERROR_PROT) {
            QMessageBox::warning(this, "MapSelector Error: ", "Match name already exists.");
            return;
        } else {
            QMessageBox::warning(this, "MapSelector Error: ", "Received an unexpected response");
            this->done(ERROR);
        }
    } catch (const ClosedQueue& e) {
        QMessageBox::warning(
                this, "MapSelector Error: ", "The response queue or command queue was closed");
        reject();

    } catch (const std::exception& e) {
        QMessageBox::warning(this, "MapSelector Error: ", "Could not connect to the server");
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
    MapEditorLobby map_editor_lobby(q_cmds, q_responses, selected_map, new_map_info);
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
