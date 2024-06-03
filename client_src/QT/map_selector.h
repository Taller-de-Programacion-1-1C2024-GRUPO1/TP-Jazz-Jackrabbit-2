#ifndef MAP_SELECTOR_H
#define MAP_SELECTOR_H
#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <string>

#include "character_selector.h"

namespace Ui {
class MapSelector;
}

class MapSelector: public QDialog {
    Q_OBJECT


public:
    explicit MapSelector(QWidget* parent = nullptr);
    ~MapSelector();

    QString get_selected_map() const;

private slots:
    void on_btnMap1_clicked();

    void on_btnMap2_clicked();

    void on_btnMapCreate_clicked();



private:
    Ui::MapSelector* ui;
    QString selected_map;
};

#endif  // MAP_SELECTOR_H
