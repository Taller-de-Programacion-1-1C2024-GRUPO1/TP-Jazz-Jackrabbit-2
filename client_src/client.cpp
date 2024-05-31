#include "client.h"


Client::Client(const std::string& host, const std::string& service):
        protocol(std::move(host), std::move(service)),
        q_cmds(15),  // ESE 15 HAY QUE SACARLO ////////////////////////////////// ACA HAY QUE USAR
                     // PUNTEROS INTELIGENTES
        q_snapshots(),
        client_sender(protocol, q_cmds),
        client_receiver(protocol, q_snapshots),
        drawer(q_cmds, q_snapshots) {}


void Client::run(int argc, char* argv[]) {
    client_sender.start();
    client_receiver.start();

    // QT
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(resources);
    ClientLobby w;
    w.show();
    a.exec();

    // SDL
    drawer.run();
}

Client::~Client() {
    this->protocol.~Protocol();
    client_sender.kill();
    client_receiver.kill();
    client_receiver.join();
    client_sender.join();
}
