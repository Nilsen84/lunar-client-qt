#include <QApplication>
#include <QStandardPaths>
#include <QCommandLineParser> 

#include "gui/mainwindow.h"
#include "launch/offlinelauncher.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName(QStringLiteral("lunar-client-qt"));

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption noGuiOption("nogui",
        QCoreApplication::translate("main", "Launch Lunar Client Qt without GUI. Useful when making a shortcut and uses configurations used previously."));
    parser.addOption(noGuiOption);
    parser.process(app);

    if (parser.isSet(noGuiOption)) {
        OfflineLauncher(Config::load(), nullptr).launch();
    }
    else {
        MainWindow mainWindow;
        mainWindow.show();
        return QApplication::exec();
    }
}
