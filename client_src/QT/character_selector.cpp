#include "character_selector.h"

#include "ui_character_selector.h"


CharacterSelector::CharacterSelector(QWidget* parent):
        QDialog(parent), ui(new Ui::CharacterSelector) {
    ui->setupUi(this);
    qt_common_init(this, ":/backgrounds/match_lobby.png");
}

CharacterSelector::~CharacterSelector() { delete ui; }


void CharacterSelector::on_btnCharacterJazz_clicked() { selectCharacter(Jazz); }


void CharacterSelector::on_btnCharacterLori_clicked() { selectCharacter(Lori); }


void CharacterSelector::on_btnCharacterSpaz_clicked() { selectCharacter(Spaz); }


void CharacterSelector::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}

void CharacterSelector::selectCharacter(ChampionType character) {
    if (ui->txtPlayerName->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a player name");
        return;
    }
    emit characterSelected(character, ui->txtPlayerName->toPlainText().toStdString());
    accept();
}
