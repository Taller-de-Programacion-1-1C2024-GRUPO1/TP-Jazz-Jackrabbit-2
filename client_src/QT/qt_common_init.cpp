#include "qt_common_init.h"

#include <QApplication>
#include <QDebug>
#include <QFontDatabase>
#include <QPalette>
#include <QPixmap>

QString qt_common_init(QWidget* widget, const QString& backgroundPath) {
    QPixmap pixmap(backgroundPath);
    QSize windowSize = widget->size();
    QPixmap scaledPixmap = pixmap.scaled(windowSize, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledPixmap);
    widget->setPalette(palette);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/04B_30__.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(fontFamily);
        QApplication::setFont(font);
        return fontFamily;
    } else {
        qWarning() << "Could not load font: "
                   << "04B_30__.ttf";
        return "";
    }
}
