#ifndef MAP_SELECTOR_H
#define MAP_SELECTOR_H
#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <string>

#include "match_lobby.h"

namespace Ui {
class MapSelector;
}

class MapSelector: public QDialog {
    Q_OBJECT
private:
    std::string map;

public:
    explicit MapSelector(QWidget* parent = nullptr);
    ~MapSelector();

private slots:
    void on_btnMap1_clicked();

    void on_btnMap2_clicked();

    void on_btnMapCreate_clicked();

    void on_btnContinue_clicked();

private:
    Ui::MapSelector* ui;
};

#endif  // MAP_SELECTOR_H
