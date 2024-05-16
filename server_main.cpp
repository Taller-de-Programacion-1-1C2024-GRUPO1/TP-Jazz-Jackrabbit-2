#include "server_src/server.h"
#include "server_src/config.h"

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

        std::string config_file = "external/config/config.yaml";
        ConfigSingleton::getInstance(config_file);
        Server server(servname);
        server.run();

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
