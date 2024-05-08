#include <exception>
#include <iostream>

#include "../common_src/common_resolver.h"

#include "client.h"

/*
gdb --tui ./server
start 8080

./server 8080
tiburoncin -o -A 127.0.0.1:8081 -B 127.0.0.1:8080
./client localhost 8081


./run_tests.sh . casos/ multi-client no-valgrind 60 10 no
./compare_outputs.sh casos/ salidas/

pre-commit run --hook-stage manual --files xxx.cpp
pre-commit run --hook-stage manual --all-files
*/


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

        Client cliente(std::move(hostname), std::move(servname));
        cliente.run();
        return 0;

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
