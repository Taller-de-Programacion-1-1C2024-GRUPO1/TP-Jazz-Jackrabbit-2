#ifndef TOP_SCORES_H
#define TOP_SCORES_H

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "client_fonts_printer.h"

#define SPACE_BETWEEN_LETTERS 12
#define SPACE_BETWEEN_WORDS 24
#define LETTERS_SIZE 24

class TopScores {
private:
    FontPrinter fontPrinter;
    std::vector<std::pair<int, int>> current_snapshot_scores;
    std::vector<std::pair<int, std::string>> current_snapshot_names;
    int player_id;

public:
    explicit TopScores(SDL2pp::Renderer& renderer, int player_id):
            fontPrinter(renderer), player_id(player_id) {
        fontPrinter.setCorner(2);
    }
    void clearCurrentSnapshotScores() { current_snapshot_scores.clear(); }

    void addCurrentSnapshotScore(int player_id, std::string player_name, int score) {
        // Find the player_id in vector
        auto it = std::find_if(
                current_snapshot_scores.begin(), current_snapshot_scores.end(),
                [player_id](const std::pair<int, int>& pair) { return pair.first == player_id; });
        if (it != current_snapshot_scores.end()) {
            it->second = score;
        } else {
            current_snapshot_scores.push_back(std::make_pair(player_id, score));
            current_snapshot_names.push_back(std::make_pair(player_id, player_name));
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
            fontPrinter.renderNumber(i + 1, offset_x, -offset_y, LETTERS_SIZE);
            offset_x += 18;
            fontPrinter.renderLetter('-', offset_x, -offset_y, LETTERS_SIZE);
            offset_x += SPACE_BETWEEN_WORDS;

            // Find the player_id in names vector
            auto it = std::find_if(current_snapshot_names.begin(), current_snapshot_names.end(),
                                   [this, i](const std::pair<int, std::string>& pair) {
                                       return pair.first == current_snapshot_scores[i].first;
                                   });
            if (it != current_snapshot_names.end()) {
                std::string name = it->second;
                for (char c: name) {
                    fontPrinter.renderLetter(std::toupper(c), offset_x, -offset_y, LETTERS_SIZE);
                    offset_x += SPACE_BETWEEN_LETTERS;
                }
            }
            if (current_snapshot_scores[i].first == player_id) {
                fontPrinter.renderLetter('*', offset_x, -offset_y, LETTERS_SIZE);
                offset_x += SPACE_BETWEEN_LETTERS;
            }

            // Print :
            offset_x += SPACE_BETWEEN_LETTERS;
            fontPrinter.renderLetter(':', offset_x, -offset_y, LETTERS_SIZE);

            // render each number on score
            offset_x += SPACE_BETWEEN_WORDS;
            std::string scoreStr = std::to_string(current_snapshot_scores[i].second);
            for (char c: scoreStr) {
                int number = c - '0';
                fontPrinter.renderNumber(number, offset_x, -offset_y, LETTERS_SIZE);
                offset_x += SPACE_BETWEEN_LETTERS;
            }
            offset_y += 32;
            offset_x = 0;
        }
    }

    void getTopScores(std::vector<std::pair<int, int>>& top_scores) {
        top_scores = current_snapshot_scores;
    }

    void getTopNames(std::vector<std::pair<int, std::string>>& top_names) {
        top_names = current_snapshot_names;
    }
};

#endif  // TOP_SCORES_H
