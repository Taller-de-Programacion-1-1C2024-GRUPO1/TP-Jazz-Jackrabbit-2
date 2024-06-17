#include "client.h"

Client::Client(const std::string& host, const std::string& service):
        protocol(std::move(host), std::move(service)),
        q_cmds(Queue<std::unique_ptr<Command>>()),
        q_responses(Queue<std::unique_ptr<QtResponse>>()),
        player_id(-1),
        map_texture(CARROTUS),
        q_snapshots(),
        client_sender(protocol, q_cmds),
        client_receiver(protocol, q_responses, q_snapshots, player_id, q_cmds),
        drawer(q_cmds, q_snapshots),
        new_map_info() {}


void Client::run(int argc, char* argv[]) {
    client_sender.start();
    client_receiver.start();

    // QT
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(resources);
    ClientLobby w(q_cmds, q_responses, new_map_info, map_texture);
    w.show();
    int result = a.exec();

    if (result == OK) {
        // SDL
        drawer.run(player_id, map_texture);
    } else if (result == OK_MAP_CREATOR) {
        // create map
        std::cout << "Creando mapa" << std::endl;
        Editor editor(new_map_info.texture, new_map_info.width, new_map_info.height,
                      new_map_info.map_name, new_map_info.max_players);
        editor.run();
    } else if (result == EDIT_MAP) {
        // edit map
        std::cout << "EDITANDO MAPA: " << new_map_info.map_name << std::endl;

    } else {
        std::cerr << "Cerrando QT" << std::endl;
    }
}

Client::~Client() {
    this->protocol.~Protocol();
    client_sender.kill();
    client_receiver.kill();
    client_receiver.join();
    client_sender.join();
}
