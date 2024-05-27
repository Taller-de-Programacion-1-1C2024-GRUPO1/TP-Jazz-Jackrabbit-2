#include "client.h"

#include "QT/client_lobby.h"


Client::Client(const std::string& host, const std::string& service):
        drawer(std::move(host), std::move(service)) {}


void Client::run(int argc, char* argv[]) {
    QApplication a(argc, argv);
    ClientLobby w;
    w.show();
    a.exec();

    // 7. Run the SDL drawer (assuming it's independent of the main window thread)
    drawer.run();
}
