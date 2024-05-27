#include "client.h"
#include <string>
#include <QApplication>

#include "../client_src/QT/client_lobby.h"

Client::Client(const std::string& host, const std::string& service):
        //lobby(), 
        renderer(std::move(host), std::move(service)) {}


void Client::run(int argc, char* argv[]) {
    //Corro QT
    QApplication a(argc, argv);
    ClientLobby w;
    w.show();
    a.exec();

    //Corro el SDL
    renderer.run();
}
