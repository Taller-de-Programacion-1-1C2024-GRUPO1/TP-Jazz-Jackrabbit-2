#ifndef MATCH_LOBBY_H
#define MATCH_LOBBY_H

#include <QDialog>

namespace Ui {
class MatchLobby;
}

class MatchLobby: public QDialog {
    Q_OBJECT
private:
    std::string map;

public:
    explicit MatchLobby(QWidget* parent = nullptr);
    ~MatchLobby();

private slots:
    void on_btnMap1_clicked();

    void on_btnMap2_clicked();

    void on_btnMapCreate_clicked();

    void on_btnContinue_clicked();

private:
    Ui::MatchLobby* ui;
};

#endif  // MATCH_LOBBY_H
