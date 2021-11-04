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

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    QListWidget* pageList;
    QStackedWidget* pages;
    QPushButton* launchButton;
    QPushButton* launchOfflineButton;
    QComboBox* versionSelect;
};


#endif //LUNAR_CLIENT_QT_MAINWINDOW_H
