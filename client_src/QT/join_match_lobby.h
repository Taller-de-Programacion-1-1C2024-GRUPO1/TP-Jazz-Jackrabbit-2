#ifndef JOIN_MATCH_LOBBY_H
#define JOIN_MATCH_LOBBY_H


#include <memory>
#include <string>
#include <vector>

#include "waiting_room.h"


namespace Ui {
class JoinMatchLobby;
}

class JoinMatchLobby: public QDialog {
    Q_OBJECT

public:
    explicit JoinMatchLobby(Queue<std::unique_ptr<Command>>& q_cmds,
                            Queue<std::unique_ptr<QtResponse>>& q_responses,
                            ChampionType selected_character, const std::string& player_name,
                            QWidget* parent = nullptr);
    ~JoinMatchLobby();

signals:
    void windowClosed();

protected:
    void closeEvent(QCloseEvent* event) override;


private slots:
    void on_btnJoin_clicked();

    void on_btnRefresh_clicked();

    void processResponse(const std::string& errorMessage,
                         std::function<void(std::unique_ptr<QtResponse>&)> handleResponse);

private:
    Ui::JoinMatchLobby* ui;
    Queue<std::unique_ptr<Command>>& q_cmds;
    Queue<std::unique_ptr<QtResponse>>& q_responses;
    ChampionType selected_character;
    std::string player_name;
};

#endif
