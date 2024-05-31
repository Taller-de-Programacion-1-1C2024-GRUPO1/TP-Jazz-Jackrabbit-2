#ifndef MATCH_LOBBY_H
#define MATCH_LOBBY_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MatchLobby;
}

class MatchLobby: public QDialog {
    Q_OBJECT

public:
    explicit MatchLobby(QWidget* parent = nullptr);
    ~MatchLobby();

private slots:
    void on_btnStart_clicked();

private:
    Ui::MatchLobby* ui;
};

#endif  // MATCH_LOBBY_H
