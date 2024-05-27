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
    explicit ClientLobby(QWidget* parent = nullptr);
    ~ClientLobby();

private:
    Ui::ClientLobby* ui;
};
#endif  // CLIENT_LOBBY_H
