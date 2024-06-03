#ifndef WAITING_ROOM_H
#define WAITING_ROOM_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>

#include "../../common_src/constants.h"
#include "../client_sender.h"
#include "../client_receiver.h"
#include "../../game_src/commands/command.h"
#include "../../game_src/commands/command_match.h"
#include <memory> 

namespace Ui {
class WaitingRoom;
}


class WaitingRoom: public QDialog {
    Q_OBJECT

public:
    explicit WaitingRoom(ClientSender& sender,  ClientReceiver& receiver, QWidget* parent = nullptr);
    ~WaitingRoom();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WaitingRoom* ui;
    ClientSender& sender;
    ClientReceiver& receiver;
};

#endif  // WAITING_ROOM_H
