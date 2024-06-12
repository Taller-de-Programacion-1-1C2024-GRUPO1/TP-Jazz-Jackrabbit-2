#include "server_receiver.h"

#include "../game_src/commands/command.h"
ServerReceiver::ServerReceiver(Protocol& protocol,
                               Queue<std::shared_ptr<Command>>& client_cmds_queue,
                               bool& keep_talking):
        protocol(protocol), client_cmds_queue(client_cmds_queue), keep_talking(keep_talking) {}


void ServerReceiver::run() {
    try {
        while (keep_talking) {
            std::shared_ptr<Command> command = protocol.receive_Command();
            client_cmds_queue.push(command);
        }
    } catch (const SocketClosed& e) {
        keep_talking = false;
        return;
    } catch (const ClosedQueue& e) {
        keep_talking = false;
        return;
    } catch (const std::exception& e) {
        keep_talking = false;
        return;
    }
}
