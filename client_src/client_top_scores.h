#ifndef TOP_SCORES_H
#define TOP_SCORES_H

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "client_number_images.h"

#define SPACE_BETWEEN_LETTERS 12
#define SPACE_BETWEEN_WORDS 24
#define LETTERS_SIZE 24

class TopScores {
private:
    NumberImages numberImages;
    std::vector<std::pair<int, int>> current_snapshot_scores;
    int player_id;

public:
    explicit TopScores(SDL2pp::Renderer& renderer, int player_id):
            numberImages(renderer), player_id(player_id) {
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
            numberImages.renderNumber(i + 1, offset_x, -offset_y, LETTERS_SIZE);
            offset_x += 18;
            numberImages.renderNumber(11, offset_x, -offset_y, LETTERS_SIZE);
            offset_x += SPACE_BETWEEN_WORDS;

            if (current_snapshot_scores[i].first == player_id) {
                // Print "YOU"
                numberImages.renderNumber(15, offset_x, -offset_y, LETTERS_SIZE);
                offset_x += SPACE_BETWEEN_LETTERS;
                numberImages.renderNumber(19, offset_x, -offset_y, LETTERS_SIZE);
                offset_x += SPACE_BETWEEN_LETTERS;
                numberImages.renderNumber(20, offset_x, -offset_y, LETTERS_SIZE);
            } else {
                // Print "PLAYER"
                for (int j = 12; j < 18; j++) {
                    numberImages.renderNumber(j, offset_x, -offset_y, LETTERS_SIZE);
                    offset_x += SPACE_BETWEEN_LETTERS;
                }
                // Print id
                offset_x += 10;
                numberImages.renderNumber(current_snapshot_scores[i].first, offset_x, -offset_y,
                                          LETTERS_SIZE);
            }
            // Print :
            offset_x += SPACE_BETWEEN_LETTERS;
            numberImages.renderNumber(18, offset_x, -offset_y, LETTERS_SIZE);
            // render each number on score
            offset_x += SPACE_BETWEEN_WORDS;
            std::string scoreStr = std::to_string(current_snapshot_scores[i].second);
            for (char c: scoreStr) {
                int number = c - '0';
                numberImages.renderNumber(number, offset_x, -offset_y, LETTERS_SIZE);
                offset_x += SPACE_BETWEEN_LETTERS;
            }
            offset_y += 32;
            offset_x = 0;
        }
    }

    void getTopScores(std::vector<std::pair<int, int>>& top_scores) {
        top_scores = current_snapshot_scores;
    }
};

#endif  // TOP_SCORES_H
