#ifndef WAITING_ROOM_H
#define WAITING_ROOM_H


#include <memory>

#include "qt_common_init.h"

namespace Ui {
class WaitingRoom;
}

class WaitingRoom: public QDialog {
    Q_OBJECT

public:
    explicit WaitingRoom(Queue<std::unique_ptr<Command>>& q_cmds,
                         Queue<std::unique_ptr<QtResponse>>& q_responses,
                         QWidget* parent = nullptr);
    ~WaitingRoom();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void startWaitingForGame();
    void stopWaitingForGame();

    Ui::WaitingRoom* ui;
    Queue<std::unique_ptr<Command>>& q_cmds;
    Queue<std::unique_ptr<QtResponse>>& q_responses;
    std::thread waiting_thread;
    std::atomic<bool> stop_thread;
};

#endif
