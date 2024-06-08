#include "map_selector.h"

#include "ui_map_selector.h"

MapSelector::MapSelector(Queue<std::unique_ptr<Command>>& q_cmds, Queue<int>& q_responses,
                         ChampionType selected_character, QWidget* parent):
        QDialog(parent),
        ui(new Ui::MapSelector),
        q_cmds(q_cmds),
        q_responses(q_responses),
        selected_character(selected_character) {
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
    selected_map = "carrotus";  // Set the map name
    start_match();
}

void MapSelector::on_btnMap2_clicked() {
    selected_map = "carrotus";  // Set the map name
    start_match();
}

void MapSelector::on_btnMapCreate_clicked() {
    hide();
    MapCreatorLobby map_creator_lobby;
    connect(&map_creator_lobby, &MapCreatorLobby::windowClosed, this,
            &MapSelector::handleWindowClosed);

    int result = map_creator_lobby.exec();
    if (result == QDialog::Accepted) {
        QApplication::exit(-2);  // Exit to start the map designer
    } else {
        this->done(-3);  // Custom exit code for closing the map creator
    }
}

void MapSelector::handleWindowClosed() { QApplication::exit(-1); }

void MapSelector::start_match() {
    int number_of_players = ui->spinNumberOfPlayers->value();
    std::string match_name = ui->txtMatchName->toPlainText().toStdString();
    if (match_name.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a match name.");
        return;
    }

    q_cmds.push(std::make_unique<MatchCommand>(NEW_MATCH, number_of_players, match_name,
                                               selected_map, selected_character));

    bool could_pop = false;
    int response;
    while (!could_pop) {
        could_pop = q_responses.try_pop(response);
    }
    if (response == 0) {
        hide();
        WaitingRoom waiting_room(q_cmds, q_responses);
        if (waiting_room.exec() == QDialog::Accepted) {
            this->done(QDialog::Accepted);
        } else {
            std::cerr << "Error en waiting room" << std::endl;
            this->done(-1);  // Custom exit code for waiting room failure
        }
    } else if (response == -1) {
        // Couldn't connect
        QMessageBox::warning(this, "Error", "Match name already exists.");
        this->done(-1);  // Custom exit code for existing match name
    } else {
        QMessageBox::warning(this, "Error", "Received an unexpected response.");
        this->done(-1);  // Custom exit code for unexpected response
    }
}

void MapSelector::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}
