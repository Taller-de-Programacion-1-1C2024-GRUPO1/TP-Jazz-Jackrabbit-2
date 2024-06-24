#include "client.h"

Client::Client(const std::string& host, const std::string& service):
        protocol(std::move(host), std::move(service)),
        q_cmds(Queue<std::unique_ptr<Command>>()),
        q_responses(Queue<std::unique_ptr<QtResponse>>()),
        player_id(-1),
        q_snapshots(),
        client_sender(protocol, q_cmds),
        client_receiver(protocol, q_responses, q_snapshots, player_id, q_cmds),
        drawer(q_cmds, q_snapshots),
        new_map_info() {}


void Client::run(int argc, char* argv[]) {
    try {
        client_sender.start();
        client_receiver.start();

        // QT
        QApplication a(argc, argv);
        Q_INIT_RESOURCE(resources);
        ClientLobby w(q_cmds, q_responses, new_map_info);
        w.show();
        int qt_result = a.exec();

        // SDL
        if (qt_result == OK) {
            drawer.run(player_id);
        } else if (qt_result == OK_MAP_CREATOR) {
            Editor editor(new_map_info.texture, new_map_info.width, new_map_info.height,
                          new_map_info.map_name, new_map_info.max_players);
            editor.run();
        } else if (qt_result == EDIT_MAP) {
            Editor editor(new_map_info.map_name);
            editor.run();

        } else {
            std::cerr << "Closing Lobby..." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}

Client::~Client() {
    this->protocol.~Protocol();
    client_sender.kill();
    client_receiver.kill();
    client_receiver.join();
    client_sender.join();
}
