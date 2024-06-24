#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <memory>
#include <string>

#include "character_selector.h"
#include "join_match_lobby.h"
#include "map_selector.h"

namespace Ui {
class ClientLobby;
}

class ClientLobby: public QMainWindow {
    Q_OBJECT

public:
    explicit ClientLobby(Queue<std::unique_ptr<Command>>& q_cmds,
                         Queue<std::unique_ptr<QtResponse>>& q_responses, NewMapInfo& new_map_info,
                         QWidget* parent = nullptr);
    ~ClientLobby();

private slots:
    void on_btnCreateMatch_clicked();
    void on_btnJoinMatch_clicked();
    void on_btnQuit_clicked();
    void handleWindowClosed();
    void handleCharacterSelected(ChampionType character, const std::string& selected_player_name);


protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::ClientLobby* ui;
    Queue<std::unique_ptr<Command>>& q_cmds;
    Queue<std::unique_ptr<QtResponse>>& q_responses;
    ChampionType selected_character;
    std::string player_name;
    NewMapInfo& new_map_info;
};

#endif
