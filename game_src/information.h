#ifndef INFO_H
#define INFO_H

#include "../common_src/protocol.h"

class Protocol;

class Information {

private:
    int InfoType = -1;

public:
    Information() {}
    ~Information() {}
    virtual void send(Protocol& protocol) = 0;
    virtual int get_infoType() = 0;
};

#endif
