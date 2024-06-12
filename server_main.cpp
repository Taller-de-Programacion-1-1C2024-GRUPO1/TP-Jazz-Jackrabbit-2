#include "server_src/config.h"
#include "server_src/server_acceptor.h"

int main(int argc, char* argv[]) {
    try {
        int ret = -1;
        const char* servname = NULL;
        if (argc == 2) {
            servname = argv[1];
        } else {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servname>\n";
            return ret;
        }

        std::string config_file = "/etc/jazz/config.yml";
        ConfigSingleton::getInstance(config_file);
        std::string map_routes = "/etc/jazz/maps.txt";
        bool server_running = true;
        ServerAcceptor server_acceptor(servname, map_routes, server_running);
        server_acceptor.start();
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line == "q") {
                server_running = false;
                server_acceptor.stop();
                server_acceptor.join();
                break;
            }
        }

        ret = 0;
        return ret;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
