//
// Created by nils on 11/4/21.
//

#ifndef LUNAR_CLIENT_QT_MAINWINDOW_H
#define LUNAR_CLIENT_QT_MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QComboBox>
#include <QStandardPaths>

#include "launch/offlinelauncher.h"
#include "launch/launcher.h"
#include "pages/configurationpage.h"
#include "pages/generalpage.h"
#include "pages/agentspage.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void load();
    void save();

    void launch(Launcher& launcher);

    void closeEvent(QCloseEvent* closeEvent) override;
private slots:
    void resetLaunchButtons();
    void launchOffline();
private:
    QListWidget* pageList;
    QStackedWidget* pageStack;
    QPushButton* launchOfflineButton;
    QComboBox* versionSelect;

    GeneralPage* generalPage;
    AgentsPage* classpathPage;

    OfflineLauncher offlineLauncher;

    static inline const QString configLocation = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/lunar-client-qt/config.json";
};


#endif //LUNAR_CLIENT_QT_MAINWINDOW_H
