#include "join_match_lobby.h"

#include "ui_join_match_lobby.h"


JoinMatchLobby::JoinMatchLobby(Queue<std::unique_ptr<Command>>& q_cmds,
                               Queue<std::unique_ptr<QtResponse>>& q_responses,
                               ChampionType selected_character, const std::string& player_name,
                               QWidget* parent):
        QDialog(parent),
        ui(new Ui::JoinMatchLobby),
        q_cmds(q_cmds),
        q_responses(q_responses),
        selected_character(selected_character),
        player_name(player_name) {
    ui->setupUi(this);
    qt_common_init(this, ":/backgrounds/match_lobby.png");
}


void JoinMatchLobby::processResponse(
        const std::string& errorMessage,
        std::function<void(std::unique_ptr<QtResponse>&)> handleResponse) {
    std::unique_ptr<QtResponse> response;
    try {
        while (true) {
            bool could_pop = q_responses.try_pop(response);
            if (could_pop) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        handleResponse(response);
    } catch (const ClosedQueue& e) {
        QMessageBox::warning(
                this, "JoinMatchLobby Error: ", "The response queue or command queue was closed");
        reject();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "JoinMatchLobby Error: ", errorMessage.c_str());
        reject();
    }
}


void JoinMatchLobby::on_btnJoin_clicked() {
    std::string match_name = ui->comboBoxMatches->currentText().toStdString();
    q_cmds.push(std::make_unique<MatchCommand>(JOIN, 0, match_name, "", selected_character,
                                               player_name));

    processResponse(
            "Could not connect to the server", [&](std::unique_ptr<QtResponse> const& response) {
                if (response->get_response() == OK) {
                    hide();
                    WaitingRoom waiting_room(q_cmds, q_responses);
                    if (waiting_room.exec() == QDialog::Accepted) {
                        accept();
                    } else {
                        std::cerr << "Error in waiting room" << std::endl;
                    }
                } else if (response->get_response() == ERROR_PROT) {
                    QMessageBox::warning(this, "Error",
                                         "Match name does not exists or has already started");
                } else {
                    QMessageBox::warning(this, "JoinMatchLobby Error: ", "Unknown response");
                }
            });
}


void JoinMatchLobby::on_btnRefresh_clicked() {
    q_cmds.push(std::make_unique<MatchCommand>(REFRESH, 0, "", "", selected_character, ""));

    processResponse(
            "Could not connect to the server", [&](std::unique_ptr<QtResponse> const& response) {
                if (response->get_info_type() == REFRESH) {
                    std::vector<std::string> matches = response->get_matches_available();
                    if (matches.empty()) {
                        QMessageBox::warning(this, "Error", "No matches available");
                        return;
                    }
                    ui->comboBoxMatches->clear();
                    for (const std::string& match: matches) {
                        ui->comboBoxMatches->addItem(QString::fromStdString(match));
                    }
                } else {
                    QMessageBox::warning(this, "JoinMatchLobby Error: ", "Unknown response");
                }
            });
}


void JoinMatchLobby::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}

JoinMatchLobby::~JoinMatchLobby() { delete ui; }
