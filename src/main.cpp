#include <QApplication>
#include <QPushButton>
#include <QStandardPaths>

#include "gui/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
