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
#include <vector>

#include "../../game_src/constants_game.h"
#include "../../game_src/qt_response.h"
#include "../client_receiver.h"
#include "../client_sender.h"

#include "waiting_room.h"

namespace Ui {
class JoinMatchLobby;
}

class JoinMatchLobby: public QDialog {
    Q_OBJECT

public:
    explicit JoinMatchLobby(Queue<std::unique_ptr<Command>>& q_cmds,
                            Queue<std::unique_ptr<QtResponse>>& q_responses,
                            ChampionType selected_character, QWidget* parent = nullptr);
    ~JoinMatchLobby();

signals:
    void windowClosed();

protected:
    void closeEvent(QCloseEvent* event) override;


private slots:
    void on_btnJoin_clicked();

    void on_btnRefresh_clicked();

private:
    Ui::JoinMatchLobby* ui;
    Queue<std::unique_ptr<Command>>& q_cmds;
    Queue<std::unique_ptr<QtResponse>>& q_responses;
    ChampionType selected_character;
};

#endif  // JOIN_MATCH_LOBBY_H
