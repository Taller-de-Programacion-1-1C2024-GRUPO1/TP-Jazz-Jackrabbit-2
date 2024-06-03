#ifndef JOIN_MATCH_LOBBY_H
#define JOIN_MATCH_LOBBY_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <string>

#include "../client_sender.h"
#include "../client_receiver.h"
#include "../../game_src/constants_game.h"
#include "waiting_room.h"

namespace Ui {
class JoinMatchLobby;
}

class JoinMatchLobby: public QDialog {
    Q_OBJECT

public:
    explicit JoinMatchLobby(ClientSender& sender, ClientReceiver& receiver, ChampionType selected_character,
                            QWidget* parent = nullptr);
    ~JoinMatchLobby();

signals:
    void windowClosed();

protected:
    void closeEvent(QCloseEvent* event) override;


private slots:
    void on_btnJoin_clicked();

private:
    Ui::JoinMatchLobby* ui;
    ClientSender& sender;
    ClientReceiver& receiver;
    ChampionType selected_character;
};

#endif  // JOIN_MATCH_LOBBY_H
