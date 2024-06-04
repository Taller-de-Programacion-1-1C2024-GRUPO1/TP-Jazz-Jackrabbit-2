#include "client.h"


Client::Client(const std::string& host, const std::string& service):
        protocol(std::move(host), std::move(service)),
        q_cmds(15),  // ESE 15 HAY QUE SACARLO ////////////////////////////////// ACA HAY QUE USAR
                     // PUNTEROS INTELIGENTES
        q_responses(),
        game_started(false),
        player_id(-1),
        q_snapshots(),
        client_sender(protocol, q_cmds),
        client_receiver(protocol, q_responses, game_started, q_snapshots),
        drawer(q_cmds, q_snapshots) {}


void Client::run(int argc, char* argv[]) {
    client_sender.start();
    client_receiver.start();

    // QT
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(resources);
    ClientLobby w(q_cmds, q_responses, game_started, player_id);
    w.show();
    int result = a.exec();

    if (result == 0) {
        // SDL
        drawer.run();
    } else {
        // error
    }
}

Client::~Client() {
    this->protocol.~Protocol();
    client_sender.kill();
    client_receiver.kill();
    client_receiver.join();
    client_sender.join();
}
