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
#include "../client_sender.h"
#include "../client_receiver.h"
#include "../../game_src/commands/command.h"
#include "../../game_src/commands/command_match.h"

namespace Ui {
class CharacterSelector;
}

class CharacterSelector: public QDialog {
    Q_OBJECT

public:
    explicit CharacterSelector(ClientSender& sender,  ClientReceiver& receiver,  QWidget* parent = nullptr);
    ~CharacterSelector();

signals:
    void windowClosed();
    void characterSelected(const std::string& character);

private slots:


    void on_btnCharacterJazz_clicked();

    void on_btnCharacterLori_clicked();

    void on_btnCharacterSpaz_clicked();


protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::CharacterSelector* ui;
    ClientSender& sender;
    ClientReceiver& receiver;
};

#endif  // CHARACTER_SELECTOR_H
