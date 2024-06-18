#ifndef QT_COMMON_INIT_H
#define QT_COMMON_INIT_H

#include <QApplication>
#include <QDebug>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QDialog>

#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <atomic>

#include "../../game_src/constants_game.h"
#include "../../game_src/qt_response.h"
#include "../../common_src/constants.h"
#include "../../common_src/queue.h"
#include "../../game_src/commands/command.h"
#include "../../game_src/commands/command_match.h"
#include "../client_constants.h"
#include "../new_map_info.h"

QString qt_common_init(QWidget* widget, const QString& backgroundPath);

#endif 