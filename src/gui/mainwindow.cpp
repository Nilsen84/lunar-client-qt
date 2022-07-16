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
#include <QLabel>

#include "pages/configurationpage.h"
#include "pages/generalpage.h"
#include "pages/minecraftpage.h"
#include "launch/launcher.h"
#include "buildconfig.h"
#include "widgets/widgetutils.h"
#include "util/utils.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), config(Config::load()), offlineLauncher(config) {
    setWindowTitle(QStringLiteral("Lunar Client Qt - Version: ") + BuildConfig::VERSION);
    QGridLayout *mainLayout = new QGridLayout();

    pageList = new QListWidget();
    pageStack = new QStackedWidget();

    pageStack->setContentsMargins(30, 10, 30, 10);

    pageList->setIconSize(QSize(32, 32));

    pages = {
            new GeneralPage(config),
            new MinecraftPage(config),
            new AgentsPage(config)
    };

    for(ConfigurationPage* page : pages){
        new QListWidgetItem(page->icon(), page->title(), pageList);
        pageStack->addWidget(page);
    }

    connect(pageList, &QListWidget::currentRowChanged, pageStack, &QStackedWidget::setCurrentIndex);

    pageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pageList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    pageList->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    QFont font;
    font.setPointSize(11);
    pageList->setFont(font);

    versionSelect = new QComboBox();
    versionSelect->addItems(Utils::getOrderedAvailableVersions());

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


    QFrame *frame = new QFrame;
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Sunken);

    QLabel *title = new QLabel;
    QFont titleFont;
    titleFont.setPointSize(13);
    title->setFont(titleFont);
    QLabel *description = new QLabel;

    QVBoxLayout *frameLayout = new QVBoxLayout(frame);

#ifdef INCLUDE_UPDATER
    QHBoxLayout *titleBtnLayout = new QHBoxLayout;
    QPushButton *checkForUpdates = new QPushButton("Check for updates");
    titleBtnLayout->addWidget(title, 1);
    titleBtnLayout->addWidget(checkForUpdates);

    frameLayout->addLayout(titleBtnLayout);

    connect(checkForUpdates, &QPushButton::clicked, [this]{updaterChecker.checkForUpdates(true);});
#else
    frameLayout->addWidget(title);
#endif
    frameLayout->addWidget(description);


    connect(pageList, &QListWidget::currentRowChanged, [this, title, description](int current) {
        title->setText(pages[current]->title());
        description->setText(pages[current]->description());
    });

    pageList->setCurrentRow(0);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(frame);
    layout->addWidget(pageStack, 1);
    mainLayout->addLayout(layout, 0, 1, -1, 1);

    setCentralWidget(WidgetUtils::layoutToWidget(mainLayout));
    resize(800, 600);

    load();

#ifdef INCLUDE_UPDATER
    connect(&updaterChecker, &UpdateChecker::updateAvailable, this, &MainWindow::updateAvailable);
    connect(&updaterChecker, &UpdateChecker::noUpdatesAvailable, this, &MainWindow::noUpdatesAvailable);

    updaterChecker.checkForUpdates(false);
#endif
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


void MainWindow::launch(Launcher &launcher, Launcher::CosmeticsState cosmeticsState) {
    apply();
    if(!launcher.launch(cosmeticsState))
        return;

    if (config.closeOnLaunch)
        close();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    apply();
    config.save();
    event->accept();
}

void MainWindow::apply() {
    for(ConfigurationPage *page : pages) {
        page->apply();
    }
    config.gameVersion = versionSelect->currentText();
}

void MainWindow::load() {
    for(ConfigurationPage* page : pages){
        page->load();
    }
    versionSelect->setCurrentText(config.gameVersion);
}


void MainWindow::errorCallback(const QString &message) {
    QMessageBox messageBox;
    messageBox.setText(message);
    messageBox.exec();
}

#ifdef INCLUDE_UPDATER

void MainWindow::updateAvailable(const QString &url) {
    QMessageBox messageBox;
    messageBox.setWindowTitle("Update available!");
    messageBox.setText(QString(
            "A new update is available!<br>"
            "To update LC-Qt, follow the link below:<br>"
            "<a href='%1'>%1</a>"
    ).arg(url));
    messageBox.exec();
}

void MainWindow::noUpdatesAvailable() {
    QMessageBox messageBox;
    messageBox.setWindowTitle("No updates available!");
    messageBox.setText("No updates available!");
    messageBox.exec();
}

#endif
