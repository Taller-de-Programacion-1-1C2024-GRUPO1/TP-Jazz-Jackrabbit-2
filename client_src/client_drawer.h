
#include "../common_src/protocol.h"
#include "../common_src/thread.h"

class ClientDrawer: public Thread {

private:
    ClientProtocol& protocol;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

public:
    explicit ClientDrawer(ClientProtocol& protocol);
    virtual void run() override;
    bool is_dead();
    void kill();
};
