#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <QApplication>
#include <QDebug>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <memory>
#include <string>

#include "../../common_src/constants.h"
#include "../../common_src/protocol.h"
#include "../../game_src/commands/command.h"
#include "../../game_src/commands/command_match.h"

#include "character_selector.h"
#include "join_match_lobby.h"
#include "map_selector.h"

namespace Ui {
class ClientLobby;
}

class ClientLobby: public QMainWindow {
    Q_OBJECT

public:
    explicit ClientLobby(Protocol& protocol, QWidget* parent = nullptr);
    ~ClientLobby();

private slots:
    void on_btnCreateMatch_clicked();
    void on_btnJoinMatch_clicked();
    void on_btnQuit_clicked();
    void handleWindowClosed();
    void handleCharacterSelected(const std::string& character);


private:
    Ui::ClientLobby* ui;
    Protocol& protocol;
    std::string selected_character;
};

#endif  // CLIENT_LOBBY_H
