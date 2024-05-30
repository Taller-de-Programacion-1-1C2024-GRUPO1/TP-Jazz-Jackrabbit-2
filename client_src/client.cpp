#include "client.h"

#include "QT/client_lobby.h"


Client::Client(const std::string& host, const std::string& service):
        manager(std::move(host), std::move(service)) {}


void Client::run(int argc, char* argv[]) {
    // QT
    QApplication a(argc, argv);
    ClientLobby w;
    w.show();
    a.exec();

    // SDL
    manager.run();
}
