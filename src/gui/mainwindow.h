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

#include "launch/launcher.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void resetLaunchButtons();
    void launch(bool offline);

private:
    QListWidget* pageList;
    QStackedWidget* pages;
    QPushButton* launchButton;
    QPushButton* launchOfflineButton;
    QComboBox* versionSelect;

    Launcher launcher;
};


#endif //LUNAR_CLIENT_QT_MAINWINDOW_H
