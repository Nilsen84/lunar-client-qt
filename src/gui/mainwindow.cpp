//
// Created by nils on 11/4/21.
//

#include "mainwindow.h"

#include <QGridLayout>
#include <QListWidgetItem>
#include <QComboBox>

#include "pages/configurationpage.h"
#include "pages/generalpage.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    QWidget* centralWidget = new QWidget();

    QGridLayout* mainLayout = new QGridLayout();

    pageList = new QListWidget(centralWidget);
    pageStack = new QStackedWidget(centralWidget);

    ConfigurationPage* pages[] = {
            new GeneralPage()
    };

    for(ConfigurationPage* page : pages){
        new QListWidgetItem(page->title(), pageList);
        pageStack->addWidget(page);
    }

    connect(pageList, &QListWidget::currentRowChanged, pageStack, &QStackedWidget::setCurrentIndex);

    pageList->setCurrentRow(0);
    pageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    pageList->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    QFont font;
    font.setPointSize(14);
    pageList->setFont(font);

    versionSelect = new QComboBox(centralWidget);
    versionSelect->addItem("1.7");
    versionSelect->addItem("1.8");
    versionSelect->addItem("1.12");
    versionSelect->addItem("1.16");
    versionSelect->addItem("1.17");
    versionSelect->setCurrentIndex(1);

    launchButton = new QPushButton(centralWidget);
    launchButton->setMinimumHeight(35);
    connect(launchButton, &QPushButton::pressed, [this](){ launch(false);});

    launchOfflineButton = new QPushButton(centralWidget);
    launchOfflineButton->setMinimumHeight(35);
    connect(launchOfflineButton, &QPushButton::pressed, [this](){ launch(true);});

    connect(&launcher, &Launcher::finished, this, &MainWindow::resetLaunchButtons);

    resetLaunchButtons();

    mainLayout->addWidget(pageList);
    mainLayout->addWidget(versionSelect, 1, 0);
    mainLayout->addWidget(launchOfflineButton, 2, 0);
    mainLayout->addWidget(launchButton, 3, 0);
    mainLayout->addWidget(pageStack, 0, 3, -1, 1);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

void MainWindow::resetLaunchButtons() {
    launchButton->setEnabled(true);
    launchButton->setText("Launch");

    launchOfflineButton->setEnabled(true);
    launchOfflineButton->setText("Launch Offline");
}

void MainWindow::launch(bool offline) {
    launchButton->setEnabled(false);
    launchButton->setText("Launching...");

    launchOfflineButton->setEnabled(false);
    launchOfflineButton->setText("Launching...");

    launcher.launch(offline);
}
