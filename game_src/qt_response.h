#ifndef QT_RESPONSE_H
#define QT_RESPONSE_H

#include <memory>
#include <string>
#include <vector>

#include "../common_src/protocol.h"


class QtResponse {
private:
    // response = -1 -> error
    // response = 0 -> success to conect
    // response > 0 -> client_id
    int response = INVALID_QT_RESPONSE;
    std::vector<std::string> matches_available;
    int response_type = INVALID_MATCH_TYPE;

public:
    QtResponse(const std::vector<std::string>& matches_available, const int& response_type):
            matches_available(matches_available), response_type(response_type) {}

    QtResponse(const int& response, const int& response_type):
            response(response), matches_available(), response_type(response_type) {}

    int get_response() const { return response; }

    std::vector<std::string> get_matches_available() { return matches_available; }

    void send(Protocol& protocol) { protocol.send_qt_response(this); }

    int get_info_type() const { return response_type; }
};

#endif
