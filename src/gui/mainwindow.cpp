//
// Created by nils on 11/4/21.
//

#include "mainwindow.h"

#include <QGridLayout>
#include <QListWidgetItem>
#include <QComboBox>
#include <QStatusBar>
#include <QScrollArea>

#include "pages/configurationpage.h"
#include "pages/generalpage.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    QWidget* centralWidget = new QWidget();

    QGridLayout* mainLayout = new QGridLayout();

    pageList = new QListWidget();
    pageStack = new QStackedWidget();

    pageStack->setContentsMargins(30, 10, 30, 10);

    pageList->setIconSize(QSize(32, 32));

    generalPage = new GeneralPage();

    new QListWidgetItem(generalPage->icon(), generalPage->title(), pageList);
    pageStack->addWidget(generalPage);


    connect(pageList, &QListWidget::currentRowChanged, pageStack, &QStackedWidget::setCurrentIndex);

    pageList->setCurrentRow(0);
    pageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    pageList->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    QFont font;
    font.setPointSize(14);
    pageList->setFont(font);

    versionSelect = new QComboBox();
    versionSelect->addItems({"1.7", "1.8", "1.12", "1.16", "1.17"});
    versionSelect->setCurrentIndex(1);

    launchButton = new QPushButton();
    launchButton->setMinimumHeight(35);
    connect(launchButton, &QPushButton::pressed, [this](){ launch(false);});

    launchOfflineButton = new QPushButton();
    launchOfflineButton->setMinimumHeight(35);
    connect(launchOfflineButton, &QPushButton::pressed, [this](){ launch(true);});

    connect(&launcher, &Launcher::finished, this, &MainWindow::resetLaunchButtons);

    resetLaunchButtons();

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidget(pageStack);


    mainLayout->addWidget(pageList);
    mainLayout->addWidget(versionSelect, 1, 0);
    mainLayout->addWidget(launchOfflineButton, 2, 0);
    mainLayout->addWidget(launchButton, 3, 0);
    mainLayout->addWidget(scrollArea, 0, 3, -1, 1);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
    resize(800, 600);
    statusBar()->showMessage(QStringLiteral("Ready!"));
}

void MainWindow::resetLaunchButtons() {
    launchButton->setEnabled(true);
    launchButton->setText(QStringLiteral("Launch"));

    launchOfflineButton->setEnabled(true);
    launchOfflineButton->setText(QStringLiteral("Launch Offline"));
}

void MainWindow::launch(bool offline) {
    if(!offline){
        QString launchingText = QStringLiteral("Launching...");
        launchButton->setEnabled(false);
        launchButton->setText(launchingText);

        launchOfflineButton->setEnabled(false);
        launchOfflineButton->setText(launchingText);
    }
    launcher.launch(offline, {
        .version = versionSelect->currentText(),
        .findLunarJre = !generalPage->isUsingCustomJre(),
        .customJre = generalPage->isUsingCustomJre() ? generalPage->getJrePath() : QString(),
        .initialMem = generalPage->getInitialMemory(),
        .maxMem = generalPage->getMaxMemory()
    });
}
