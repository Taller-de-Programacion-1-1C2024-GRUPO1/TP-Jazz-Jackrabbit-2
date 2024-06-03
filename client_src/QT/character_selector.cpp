#include "character_selector.h"

#include "ui_character_selector.h"

CharacterSelector::CharacterSelector(QWidget* parent): QDialog(parent), ui(new Ui::CharacterSelector) {
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


QString CharacterSelector::get_selected_character() const {
    return selected_character;
}


void CharacterSelector::on_btnCharacterJazz_clicked()
{
    selected_character = "Jazz";
    accept();
}


void CharacterSelector::on_btnCharacterLori_clicked()
{
    selected_character = "Lori";
    accept(); 
}


void CharacterSelector::on_btnCharacterSpaz_clicked()
{
    selected_character = "Spaz";
    accept();
}

