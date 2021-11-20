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

#include "launch/launcher.h"
#include "pages/configurationpage.h"
#include "pages/generalpage.h"
#include "pages/classpathpage.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void load();
    void save();

    void closeEvent(QCloseEvent* closeEvent) override;
private slots:
    void resetLaunchButtons();
    void launch(bool offline);
private:
    QListWidget* pageList;
    QStackedWidget* pageStack;
    QPushButton* launchButton;
    QPushButton* launchOfflineButton;
    QComboBox* versionSelect;

    GeneralPage* generalPage;
    ClasspathPage* classpathPage;

    Launcher launcher;

    static inline const QString configLocation = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/lunar-client-qt/config.json";
};


#endif //LUNAR_CLIENT_QT_MAINWINDOW_H
