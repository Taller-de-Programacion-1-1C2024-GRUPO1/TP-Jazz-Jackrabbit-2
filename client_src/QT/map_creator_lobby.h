#ifndef MAP_CREATOR_LOBBY_H
#define MAP_CREATOR_LOBBY_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <string>

#include "../../common_src/constants.h"
#include "../new_map_info.h"
#include "../client_constants.h"

namespace Ui {
class MapCreatorLobby;
}

class MapCreatorLobby: public QDialog {
    Q_OBJECT

public:
    explicit MapCreatorLobby(NewMapInfo& new_map_info, QWidget* parent = nullptr);
    ~MapCreatorLobby();

protected:
    void closeEvent(QCloseEvent* event) override;

signals:
    void windowClosed();

private slots:
    void on_btnTexture1_clicked();

    void on_btnTexture2_clicked();

    void on_btnTexture3_clicked();

private:
    NewMapInfo& new_map_info;
    Ui::MapCreatorLobby* ui;
    void start_creating_map(int texture);
};

#endif  // MAP_CREATOR_LOBBY_H
