#include "join_match_lobby.h"

#include <chrono>
#include <thread>

#include "ui_join_match_lobby.h"


JoinMatchLobby::JoinMatchLobby(Queue<std::unique_ptr<Command>>& q_cmds,
                               Queue<std::unique_ptr<QtResponse>>& q_responses,
                               ChampionType selected_character, QWidget* parent):
        QDialog(parent),
        ui(new Ui::JoinMatchLobby),
        q_cmds(q_cmds),
        q_responses(q_responses),
        selected_character(selected_character) {
    ui->setupUi(this);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/04B_30__.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(fontFamily);
        QApplication::setFont(font);
    } else {
        qWarning() << "No se pudo cargar la fuente 04B_30__";
    }
    QPixmap pixmap(":/backgrounds/match_lobby.png");
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);
}

JoinMatchLobby::~JoinMatchLobby() { delete ui; }


void JoinMatchLobby::on_btnJoin_clicked() {
    // std::string match_name = ui->txtMatchName->toPlainText().toStdString();
    std::string match_name = ui->comboBoxMatches->currentText().toStdString();
    q_cmds.push(std::make_unique<MatchCommand>(JOIN, 0, match_name, "", selected_character));

    std::unique_ptr<QtResponse> response;
    try {
        while (true) {
            bool could_pop = q_responses.try_pop(response);
            if (could_pop) {
                break;
            }
        }
        if (response->get_response() == OK) {
            hide();
            WaitingRoom waiting_room(q_cmds, q_responses);
            if (waiting_room.exec() == QDialog::Accepted) {
                accept();
            } else {
                std::cerr << "Error en waiting room" << std::endl;
            }
        } else if (response->get_response() == ERROR) {
            QMessageBox::warning(this, "Error",
                                 "Match name does not exists or match has already started.");
            return;
        } else {
            QMessageBox::warning(this, "Error", "RECIBI UNA RESPUESTA QUE NO DEBERIA RECIBIR");
            return;
        }
    } catch (const ClosedQueue& e) {
        QMessageBox::warning(this, "Error", "Se cerró la cola de respuestas o la cola de comandos");
        reject();

    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", "No se pudo conectar con el servidor");
        reject();
    }
}

void JoinMatchLobby::closeEvent(QCloseEvent* event) {
    emit windowClosed();
    QDialog::closeEvent(event);
}

void JoinMatchLobby::on_btnRefresh_clicked() {
    try {
        q_cmds.push(std::make_unique<MatchCommand>(REFRESH, 0, "", "", selected_character));
        bool could_pop = false;
        std::unique_ptr<QtResponse> response;
        while (!could_pop) {
            could_pop = q_responses.try_pop(response);
        }
        if (response->get_info_type() == REFRESH) {
            std::vector<std::string> matches = response->get_matches_available();
            if (matches.empty()) {
                QMessageBox::warning(this, "Error", "No hay partidas disponibles");
                return;
            }
            ui->comboBoxMatches->clear();
            for (const std::string& match: matches) {
                std::cout << "Match: " << match << std::endl;
                ui->comboBoxMatches->addItem(QString::fromStdString(match));
            }

        } else {
            QMessageBox::warning(this, "Error", "RECIBI UNA RESPUESTA QUE NO DEBERIA RECIBIR");
        }
    } catch (const ClosedQueue& e) {
        QMessageBox::warning(this, "Error", "Se cerró la cola de respuestas o la cola de comandos");
        reject();

    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", "No se pudo conectar con el servidor");
        reject();
    }
}
