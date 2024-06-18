#ifndef MAP_EDITOR_LOBBY_H
#define MAP_EDITOR_LOBBY_H

#include <memory>
#include <string>
#include <vector>

#include "qt_common_init.h"

namespace Ui {
class MapEditorLobby;
}

class MapEditorLobby: public QDialog {
    Q_OBJECT

public:
    explicit MapEditorLobby(Queue<std::unique_ptr<Command>>& q_cmds,
                            Queue<std::unique_ptr<QtResponse>>& q_responses,
                            std::string& selected_map, NewMapInfo& new_map_info,
                            QWidget* parent = nullptr);
    ~MapEditorLobby();


protected:
    void closeEvent(QCloseEvent* event) override;

signals:
    void windowClosed();

private slots:

    void on_btnRefresh_clicked();
    void on_btnPlay_clicked();
    void on_btnEdit_clicked();


private:
    Ui::MapEditorLobby* ui;
    Queue<std::unique_ptr<Command>>& q_cmds;
    Queue<std::unique_ptr<QtResponse>>& q_responses;
    std::string& selected_map;
    NewMapInfo& new_map_info;
};

#endif
