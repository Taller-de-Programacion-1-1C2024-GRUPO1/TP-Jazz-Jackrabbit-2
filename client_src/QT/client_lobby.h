#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <QApplication>
#include <QDebug>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>

#include "../../common_src/constants.h"
#include "../../common_src/protocol.h"
#include "../../game_src/commands/command.h"
#include "../../game_src/commands/command_match.h"
#include <memory> 

#include "map_selector.h"
#include "join_match_lobby.h"

namespace Ui {
    class ClientLobby;
}

class ClientLobby: public QMainWindow {
    Q_OBJECT
private:
    Protocol& protocol;
    std::unique_ptr<Ui::ClientLobby> ui; // Usar std::unique_ptr para gestionar la memoria de ui

public:
    explicit ClientLobby(Protocol& protocol);
    ~ClientLobby();

private slots:
    void on_btnCreateMatch_clicked();
    void on_btnJoinMatch_clicked();
    void on_btnQuit_clicked();

private:
    QString selected_character;
    QString selected_map;
    QString selected_match;

};

#endif  // CLIENT_LOBBY_H

