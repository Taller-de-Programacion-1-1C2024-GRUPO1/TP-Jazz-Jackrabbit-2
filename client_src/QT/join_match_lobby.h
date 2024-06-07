#ifndef JOIN_MATCH_LOBBY_H
#define JOIN_MATCH_LOBBY_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <memory>
#include <string>

#include "../../game_src/constants_game.h"
#include "../client_receiver.h"
#include "../client_sender.h"

#include "waiting_room.h"

namespace Ui {
class JoinMatchLobby;
}

class JoinMatchLobby: public QDialog {
    Q_OBJECT

public:
    explicit JoinMatchLobby(Queue<std::unique_ptr<Command>>& q_cmds, Queue<int>& q_responses,
                            ChampionType selected_character, QWidget* parent = nullptr);
    ~JoinMatchLobby();

signals:
    void windowClosed();

protected:
    void closeEvent(QCloseEvent* event) override;


private slots:
    void on_btnJoin_clicked();

private:
    Ui::JoinMatchLobby* ui;
    Queue<std::unique_ptr<Command>>& q_cmds;
    Queue<int>& q_responses;
    ChampionType selected_character;
};

#endif  // JOIN_MATCH_LOBBY_H
