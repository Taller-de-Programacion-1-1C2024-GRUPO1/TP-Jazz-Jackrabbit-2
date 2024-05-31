#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ClientLobby;
}
QT_END_NAMESPACE

class ClientLobby: public QMainWindow {
    Q_OBJECT

public:
    ClientLobby(QWidget* parent = nullptr);
    ~ClientLobby();
    //void run(int argc, char* argv[]);

private slots:
    void on_btnCreateMatch_clicked();

    void on_btnJoinMatch_clicked();

    void on_btnError_clicked();



private:
    Ui::ClientLobby* ui;
};
#endif  // CLIENT_LOBBY_H
