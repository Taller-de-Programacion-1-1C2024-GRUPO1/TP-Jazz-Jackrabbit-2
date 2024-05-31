#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <QMainWindow>
#include "../../common_src/protocol.h"
#include "../../common_src/constants.h"
#include "../../game_src/commands/command_match.h"
#include "../../game_src/commands/command.h"
#include "match_lobby.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ClientLobby;
}
QT_END_NAMESPACE

class ClientLobby: public QMainWindow {
    Q_OBJECT
private:
    Protocol& protocol;

public:
    //ClientLobby(QWidget* parent = nullptr);
    ClientLobby(Protocol& protocol);
    ~ClientLobby();
    // void run(int argc, char* argv[]);

private slots:
    void on_btnCreateMatch_clicked();

    void on_btnJoinMatch_clicked();

    void on_btnError_clicked();


private:
    Ui::ClientLobby* ui;
};
#endif  // CLIENT_LOBBY_H
