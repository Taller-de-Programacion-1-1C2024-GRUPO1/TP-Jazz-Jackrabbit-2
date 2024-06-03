#ifndef MAP_SELECTOR_H
#define MAP_SELECTOR_H
#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <memory>
#include <string>

#include "../../common_src/constants.h"
#include "../client_sender.h"
#include "../client_receiver.h"
#include "../../game_src/commands/command.h"
#include "../../game_src/commands/command_match.h"

#include "character_selector.h"
#include "waiting_room.h"

namespace Ui {
class MapSelector;
}

class MapSelector: public QDialog {
    Q_OBJECT

public:
    explicit MapSelector(ClientSender& sender,  ClientReceiver& receiver, ChampionType selected_character,
                         QWidget* parent = nullptr);
    ~MapSelector();

signals:
    void windowClosed();
    void mapSelected(int number_of_players, const std::string& selected_map);

private slots:
    void on_btnMap1_clicked();

    void on_btnMap2_clicked();

    void on_btnMapCreate_clicked();

    void start_match();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::MapSelector* ui;
    ClientSender& sender;
    ClientReceiver& receiver;
    ChampionType selected_character;
    std::string selected_map;
    std::string match_name;
};

#endif  // MAP_SELECTOR_H
