#ifndef JOIN_MATCH_LOBBY_H
#define JOIN_MATCH_LOBBY_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include "../../common_src/protocol.h"

namespace Ui {
class JoinMatchLobby;
}

class JoinMatchLobby: public QDialog {
    Q_OBJECT

public:
    explicit JoinMatchLobby(QWidget* parent = nullptr);
    ~JoinMatchLobby();

    QString get_match_name() const;

private slots:
    void on_btnJoin_clicked();

private:
    Ui::JoinMatchLobby* ui;
    QString match_name;
};

#endif  // JOIN_MATCH_LOBBY_H
