#include "character_selector.h"

#include "ui_character_selector.h"


CharacterSelector::CharacterSelector(QWidget* parent):
        QDialog(parent), ui(new Ui::CharacterSelector) {
    ui->setupUi(this);
    qt_common_init(this, ":/backgrounds/match_lobby.png");
}

CharacterSelector::~CharacterSelector() { delete ui; }


void CharacterSelector::on_btnCharacterJazz_clicked() {
    emit characterSelected(Jazz);
    accept();
}


void CharacterSelector::on_btnCharacterLori_clicked() {
    emit characterSelected(Lori);
    accept();
}


void CharacterSelector::on_btnCharacterSpaz_clicked() {
    emit characterSelected(Spaz);
    accept();
}


void CharacterSelector::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}
