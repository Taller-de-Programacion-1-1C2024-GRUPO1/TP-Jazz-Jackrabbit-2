#include <exception>
#include <iostream>

#include "client_src/client.h"
#include "client_src/client_config.h"

int main(int argc, char* argv[]) {
    try {
        const char* hostname = NULL;
        const char* servname = NULL;

        if (argc == 2) {
            hostname = argv[1];
        } else if (argc == 3) {
            hostname = argv[1];
            servname = argv[2];
        } else {
            std::cerr << "Bad program call. Expected " << argv[0] << " <hostname> [<servname>]\n";
            return -1;
        }

        std::string config_file = "/etc/jazz/client_config.yml";
        ClientConfigSingleton::getInstance(config_file);

        Client client(std::move(hostname), std::move(servname));
        client.run(argc, argv);
        return 0;

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
