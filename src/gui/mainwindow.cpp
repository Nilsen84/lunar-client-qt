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

    launchUnlockedCosmeticsButton = new QPushButton;
    launchUnlockedCosmeticsButton->setMinimumHeight(45);
    connect(launchUnlockedCosmeticsButton, &QPushButton::clicked, this, &MainWindow::launchUnlockedCosmetics);

    launchNoCosmeticsButton = new QPushButton();
    launchNoCosmeticsButton->setMinimumHeight(45);
    connect(launchNoCosmeticsButton, &QPushButton::clicked, this, &MainWindow::launchNoCosmetics);

    launchButton = new QPushButton();
    launchButton->setMinimumHeight(45);
    connect(launchButton, &QPushButton::clicked, this, &MainWindow::launchDefault);

    connect(&offlineLauncher, &OfflineLauncher::error, this, &MainWindow::errorCallback);

    resetLaunchButtons();

    mainLayout->addWidget(pageList);
    mainLayout->addWidget(versionSelect, 1, 0);
    mainLayout->addWidget(launchUnlockedCosmeticsButton, 2, 0);
    mainLayout->addWidget(launchNoCosmeticsButton, 3, 0);
    mainLayout->addWidget(launchButton, 4, 0);
    mainLayout->addWidget(pageStack, 0, 3, -1, 1);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
    resize(800, 600);

    load();
}

void MainWindow::resetLaunchButtons() {
    launchUnlockedCosmeticsButton->setEnabled(true);
    launchUnlockedCosmeticsButton->setText(QStringLiteral("Launch With All\nCosmetics"));

    launchButton->setEnabled(true);
    launchButton->setText(QStringLiteral("Launch"));

    launchNoCosmeticsButton->setEnabled(true);
    launchNoCosmeticsButton->setText(QStringLiteral("Launch Without\nCosmetics"));
}

void MainWindow::launchNoCosmetics() {
    launch(offlineLauncher, Launcher::CosmeticsState::OFF);
}

void MainWindow::launchDefault() {
    launch(offlineLauncher, Launcher::CosmeticsState::DEFAULT);
}

void MainWindow::launchUnlockedCosmetics() {
    launch(offlineLauncher, Launcher::CosmeticsState::UNLOCKED);
}


void MainWindow::launch(Launcher& launcher, Launcher::CosmeticsState cosmeticsState){
    apply();
    launcher.launch(cosmeticsState);
    if(config.closeOnLaunch)
        close();
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