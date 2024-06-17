#ifndef TOP_SCORES_H
#define TOP_SCORES_H

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "client_number_images.h"

class TopScores {
private:
    NumberImages numberImages;
    std::vector<std::pair<int, int>> current_snapshot_scores;

public:
    explicit TopScores(SDL2pp::Renderer& renderer): numberImages(renderer) {
        numberImages.setCorner(2);
    }
    void clearCurrentSnapshotScores() { current_snapshot_scores.clear(); }

    void addCurrentSnapshotScore(int player_id, int score) {
        // Find the player_id in vector
        auto it = std::find_if(
                current_snapshot_scores.begin(), current_snapshot_scores.end(),
                [player_id](const std::pair<int, int>& pair) { return pair.first == player_id; });
        if (it != current_snapshot_scores.end()) {
            it->second = score;
        } else {
            current_snapshot_scores.push_back(std::make_pair(player_id, score));
        }
    }

    void update() {
        // Sort current_snapshot_scores
        std::sort(current_snapshot_scores.begin(), current_snapshot_scores.end(),
                  [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                      return a.second > b.second;
                  });
    }

    void render() {
        int offset_x = 0;
        int offset_y = 0;
        for (int i = 2; i >= 0; i--) {
            if (i >= static_cast<int>(current_snapshot_scores.size())) {
                continue;
            }
            // Print "i-"
            numberImages.renderNumber(i + 1, offset_x, -offset_y, 24);
            offset_x += 18;
            numberImages.renderNumber(11, offset_x, -offset_y, 24);
            offset_x += 24;
            // Print "PLAYER"
            for (int j = 12; j < 18; j++) {
                numberImages.renderNumber(j, offset_x, -offset_y, 24);
                offset_x += 12;
            }
            // Print id
            offset_x += 10;
            numberImages.renderNumber(current_snapshot_scores[i].first, offset_x, -offset_y, 24);
            // Print :
            offset_x += 12;
            numberImages.renderNumber(18, offset_x, -offset_y, 24);
            // render each number on score
            offset_x += 24;
            std::string scoreStr = std::to_string(current_snapshot_scores[i].second);
            for (char c: scoreStr) {
                int number = c - '0';
                numberImages.renderNumber(number, offset_x, -offset_y, 24);
                offset_x += 24;
            }
            offset_y += 32;
            offset_x = 0;
        }
    }
};

#endif  // TOP_SCORES_H
