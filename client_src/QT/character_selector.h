#ifndef CHARACTER_SELECTOR_H
#define CHARACTER_SELECTOR_H


#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <memory>
#include <string>

#include "../../common_src/constants.h"
#include "../../game_src/commands/command.h"
#include "../../game_src/commands/command_match.h"
#include "../../game_src/constants_game.h"

#include "qt_common_init.h"

namespace Ui {
class CharacterSelector;
}

class CharacterSelector: public QDialog {
    Q_OBJECT

public:
    explicit CharacterSelector(QWidget* parent = nullptr);
    ~CharacterSelector();

signals:
    void windowClosed();
    void characterSelected(ChampionType character, const std::string& player_name);

private slots:


    void on_btnCharacterJazz_clicked();

    void on_btnCharacterLori_clicked();

    void on_btnCharacterSpaz_clicked();

    void selectCharacter(ChampionType character);


protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::CharacterSelector* ui;
};

#endif
