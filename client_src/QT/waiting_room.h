#ifndef WAITING_ROOM_H
#define WAITING_ROOM_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <atomic>
#include <memory>
#include <thread>

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
    explicit WaitingRoom(Queue<std::unique_ptr<Command>>& q_cmds, Queue<int>& q_responses,
                         QWidget* parent = nullptr);
    ~WaitingRoom();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void startWaitingForGame();
    void stopWaitingForGame();

    Ui::WaitingRoom* ui;
    Queue<std::unique_ptr<Command>>& q_cmds;
    Queue<int>& q_responses;
    std::thread waiting_thread;
    std::atomic<bool> stop_thread;
};

#endif  // WAITING_ROOM_H
