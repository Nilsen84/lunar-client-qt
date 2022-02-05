#include <QApplication>

#include "gui/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QApplication::setApplicationName(QStringLiteral("lunar-client-qt"));
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
