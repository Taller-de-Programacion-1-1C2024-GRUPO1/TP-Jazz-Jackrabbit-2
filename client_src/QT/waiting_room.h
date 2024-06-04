#ifndef WAITING_ROOM_H
#define WAITING_ROOM_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <memory>

#include "../../common_src/constants.h"
#include "../../game_src/commands/command.h"
#include "../../game_src/commands/command_match.h"
#include "../client_receiver.h"
#include "../client_sender.h"

namespace Ui {
class WaitingRoom;
}


class WaitingRoom: public QDialog {
    Q_OBJECT

public:
    explicit WaitingRoom(Queue<Command*>& q_cmds, Queue<int>& q_responses,
                         std::atomic<bool>& game_started, int& player_id,
                         QWidget* parent = nullptr);
    ~WaitingRoom();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WaitingRoom* ui;
    Queue<Command*>& q_cmds;
    Queue<int>& q_responses;
    std::atomic<bool>& game_started;
    int& player_id;
};

#endif  // WAITING_ROOM_H
