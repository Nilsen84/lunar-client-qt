//
// Created by nils on 11/4/21.
//

#include "mainwindow.h"

#include <QGridLayout>
#include <QListWidgetItem>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) {
    QWidget* centralWidget = new QWidget();

    QGridLayout* mainLayout = new QGridLayout();

    pageList = new QListWidget(centralWidget);
    new QListWidgetItem("General", pageList);

    pages = new QStackedWidget(centralWidget);
    new QWidget(pages);

    connect(pageList, &QListWidget::currentRowChanged, pages, &QStackedWidget::setCurrentIndex);

    pageList->setCurrentRow(0);
    pageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    pageList->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    QFont font;
    font.setPointSize(13);
    pageList->setFont(font);

    versionSelect = new QComboBox(centralWidget);
    versionSelect->addItem("1.7");
    versionSelect->addItem("1.8");
    versionSelect->addItem("1.12");
    versionSelect->addItem("1.16");
    versionSelect->addItem("1.17");
    versionSelect->setCurrentIndex(1);

    launchButton = new QPushButton("Launch", centralWidget);
    launchButton->setMinimumHeight(35);

    launchOfflineButton = new QPushButton("Launch Offline", centralWidget);
    launchOfflineButton->setMinimumHeight(35);

    mainLayout->addWidget(pageList);
    mainLayout->addWidget(versionSelect, 1, 0);
    mainLayout->addWidget(launchOfflineButton, 2, 0);
    mainLayout->addWidget(launchButton, 3, 0);
    mainLayout->addWidget(pages, 0, 3, -1, 1);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}
