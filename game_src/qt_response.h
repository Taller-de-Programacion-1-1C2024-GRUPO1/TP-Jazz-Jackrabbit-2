#ifndef QT_RESPONSE_H
#define QT_RESPONSE_H

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "../common_src/protocol.h"


class QtResponse {
private:
    // response = -1 -> error
    // response = 0 -> success to conect
    // response > 0 -> client_id
    int response = INVALID_QT_RESPONSE;
    std::tuple<std::vector<std::string>, std::vector<std::string>> info_available;
    int response_type = INVALID_MATCH_TYPE;

public:
    QtResponse(const std::tuple<std::vector<std::string>, std::vector<std::string>>& info_available,
               const int& response_type):
            info_available(info_available), response_type(response_type) {}

    QtResponse(const int& response, const int& response_type):
            response(response), info_available(), response_type(response_type) {}

    int get_response() const { return response; }

    std::tuple<std::vector<std::string>, std::vector<std::string>> get_info_available() {
        return info_available;
    }

    std::vector<std::string> get_matches_available() { return std::get<0>(info_available); }
    std::vector<std::string> get_maps_available() { return std::get<1>(info_available); }

    void send(Protocol& protocol) { protocol.send_qt_response(this); }

    int get_info_type() const { return response_type; }

    int get_map_texture() const { return response; }
};

#endif
