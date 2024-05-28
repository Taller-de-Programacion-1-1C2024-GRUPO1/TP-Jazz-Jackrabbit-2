#include <QApplication>
#include <QDebug>
#include <QFontDatabase>
#include <QWidget>

#include "client_lobby.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);


    // Cargar la fuente desde los recursos
    int fontId = QFontDatabase::addApplicationFont(":/fonts/04B_30__.ttf");
    if (fontId != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.empty()) {
            QFont font(fontFamilies.at(0));
            QString fontFamily = fontFamilies.at(0);
            // qDebug() << "Nombre de la familia de la fuente:" << fontFamily;
        } else {
            qWarning() << "No se encontraron familias de fuentes en el archivo";
        }
    } else {
        qWarning() << "No se pudo cargar la fuente";
    }


    ClientLobby w;
    w.show();
    return a.exec();
}
