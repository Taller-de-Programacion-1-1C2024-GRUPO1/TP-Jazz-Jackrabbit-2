#ifndef CHARACTER_SELECTOR_H
#define CHARACTER_SELECTOR_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class CharacterSelector;
}

class CharacterSelector: public QDialog {
    Q_OBJECT

public:
    explicit CharacterSelector(QWidget* parent = nullptr);
    ~CharacterSelector();
    
    QString get_selected_character() const;

private slots:


    void on_btnCharacterJazz_clicked();

    void on_btnCharacterLori_clicked();

    void on_btnCharacterSpaz_clicked();

private:
    Ui::CharacterSelector* ui;
    QString selected_character; 
};

#endif  // CHARACTER_SELECTOR_H
