#ifndef MAP_SELECTOR_H
#define MAP_SELECTOR_H


#include <memory>
#include <string>

#include "character_selector.h"
#include "map_creator_lobby.h"
#include "map_editor_lobby.h"
#include "waiting_room.h"

namespace Ui {
class MapSelector;
}

class MapSelector: public QDialog {
    Q_OBJECT

public:
    explicit MapSelector(Queue<std::unique_ptr<Command>>& q_cmds,
                         Queue<std::unique_ptr<QtResponse>>& q_responses,
                         ChampionType selected_character, NewMapInfo& new_map_info,
                         const std::string& player_name, QWidget* parent = nullptr);
    ~MapSelector();

signals:
    void windowClosed();
    void mapSelected(int number_of_players, const std::string& selected_map);

private slots:
    void on_btnMap1_clicked();

    void on_btnMap2_clicked();

    void on_btnMapCreate_clicked();

    void start_match();

    void handleWindowClosed();

    void on_btnCustomMaps_clicked();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::MapSelector* ui;
    Queue<std::unique_ptr<Command>>& q_cmds;
    Queue<std::unique_ptr<QtResponse>>& q_responses;
    ChampionType selected_character;
    std::string selected_map;
    std::string match_name;
    NewMapInfo& new_map_info;
    std::string player_name;
};

#endif  // MAP_SELECTOR_H
