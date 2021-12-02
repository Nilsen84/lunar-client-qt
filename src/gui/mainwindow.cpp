//
// Created by nils on 11/4/21.
//

#include "mainwindow.h"

#include <QGridLayout>
#include <QListWidgetItem>
#include <QComboBox>
#include <QStatusBar>
#include <QScrollArea>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QMessageBox>

#include "pages/configurationpage.h"
#include "pages/generalpage.h"
#include "pages/minecraftpage.h"
#include "launch/launcher.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), config(Config::load()), offlineLauncher(config){
    setWindowTitle(QStringLiteral("Lunar Client Qt"));
    QWidget* centralWidget = new QWidget();

    QGridLayout* mainLayout = new QGridLayout();

    pageList = new QListWidget();
    pageStack = new QStackedWidget();

    pageStack->setContentsMargins(30, 10, 30, 10);

    pageList->setIconSize(QSize(32, 32));

    pages = {
        new GeneralPage(config),
        new MinecraftPage(config),
        new AgentsPage(config)
    };

    foreach(ConfigurationPage* page, pages){
        new QListWidgetItem(page->icon(), page->title(), pageList);
        pageStack->addWidget(page);
    }

    connect(pageList, &QListWidget::currentRowChanged, pageStack, &QStackedWidget::setCurrentIndex);

    pageList->setCurrentRow(0);
    pageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    pageList->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    QFont font;
    font.setPointSize(11);
    pageList->setFont(font);

    versionSelect = new QComboBox();
    versionSelect->addItems({"1.7", "1.8", "1.12", "1.16", "1.17", "1.18"});

    launchNoCosmeticsButton = new QPushButton();
    launchNoCosmeticsButton->setMinimumHeight(45);
    connect(launchNoCosmeticsButton, &QPushButton::pressed, this, &MainWindow::launchNoCosmetics);

    launchOfflineButton = new QPushButton();
    launchOfflineButton->setMinimumHeight(45);
    connect(launchOfflineButton, &QPushButton::pressed, this, &MainWindow::launchOffline);

    connect(&offlineLauncher, &OfflineLauncher::error, this, &MainWindow::errorCallback);

    resetLaunchButtons();

    mainLayout->addWidget(pageList);
    mainLayout->addWidget(versionSelect, 1, 0);
    mainLayout->addWidget(launchNoCosmeticsButton, 2, 0);
    mainLayout->addWidget(launchOfflineButton, 3, 0);
    mainLayout->addWidget(pageStack, 0, 3, -1, 1);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
    resize(800, 600);

    load();
}

void MainWindow::resetLaunchButtons() {
    launchOfflineButton->setEnabled(true);
    launchOfflineButton->setText(QStringLiteral("Launch"));

    launchNoCosmeticsButton->setEnabled(true);
    launchNoCosmeticsButton->setText(QStringLiteral("Launch without\ncosmetics"));
}

void MainWindow::launchNoCosmetics() {
    launch(offlineLauncher, false);
}


void MainWindow::launchOffline() {
    launch(offlineLauncher, true);
}

void MainWindow::launch(Launcher& launcher, bool cosmetics){
    apply();
    launcher.launch(cosmetics);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    apply();
    config.save();
    event->accept();
}

void MainWindow::apply() {
    foreach(ConfigurationPage* page, pages){
        page->apply();
    }
    config.gameVersion = versionSelect->currentText();
}

void MainWindow::load() {
    foreach(ConfigurationPage* page, pages){
        page->load();
    }
    versionSelect->setCurrentText(config.gameVersion);
}


void MainWindow::errorCallback(const QString &message) {
    QMessageBox messageBox;
    messageBox.setText(message);
    messageBox.exec();
}
