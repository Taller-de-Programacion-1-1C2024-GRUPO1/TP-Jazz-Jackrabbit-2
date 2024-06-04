#include "character_selector.h"

#include "ui_character_selector.h"


CharacterSelector::CharacterSelector(QWidget* parent):
        QDialog(parent), ui(new Ui::CharacterSelector) {
    ui->setupUi(this);

    // Establecer el fondo
    QPixmap originalPixmap(":/backgrounds/match_lobby.png");
    QSize windowSize = this->size();
    QPixmap scaledPixmap = originalPixmap.scaled(windowSize, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledPixmap);
    this->setPalette(palette);
}

CharacterSelector::~CharacterSelector() { delete ui; }


void CharacterSelector::on_btnCharacterJazz_clicked() {
    emit characterSelected(JAZZ);
    accept();
}


void CharacterSelector::on_btnCharacterLori_clicked() {
    emit characterSelected(LORI);
    accept();
}


void CharacterSelector::on_btnCharacterSpaz_clicked() {
    emit characterSelected(SPAZ);
    accept();
}


void CharacterSelector::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}
