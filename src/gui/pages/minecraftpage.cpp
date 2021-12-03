//
// Created by nils on 12/2/21.
//

#include "minecraftpage.h"

#include <QHBoxLayout>
#include <QLabel>
#include <gui/widgets/widgetutils.h>

MinecraftPage::MinecraftPage(Config &config, QWidget *parent) : ConfigurationPage(config, parent) {
    customMinecraftDir = new QCheckBox(QStringLiteral("Custom .minecraft Directory"));

    minecraftPathChooser = new FileChooser(QFileDialog::Directory);
    minecraftPathChooser->setDisabled(true);

    connect(customMinecraftDir, &QCheckBox::toggled, minecraftPathChooser, &FileChooser::setEnabled);

    //Custom jre groups
    QVBoxLayout* customMCPathContainer = new QVBoxLayout();
    customMCPathContainer->setSpacing(6);
    customMCPathContainer->addWidget(customMinecraftDir, 0, Qt::AlignHCenter);
    customMCPathContainer->addWidget(minecraftPathChooser);

    serverToJoin = new QLineEdit();
    serverToJoin->setDisabled(true);

    connect(serverToJoin, &QLineEdit::returnPressed, [this](){serverToJoin->clearFocus();});

    joinServerOnLaunch = new QCheckBox(QStringLiteral("Join Server On Launch"));

    connect(joinServerOnLaunch, &QCheckBox::toggled, serverToJoin, &QLineEdit::setEnabled);

    QVBoxLayout* serverContainer = new QVBoxLayout();
    serverContainer->setSpacing(6);
    serverContainer->addWidget(joinServerOnLaunch, 0, Qt::AlignHCenter);
    serverContainer->addWidget(serverToJoin);

    useCustomNickHiderName = new QCheckBox(QStringLiteral("NickHider Name"));
    nickHiderName = new QLineEdit();
    nickHiderName->setPlaceholderText(QStringLiteral("You"));

    useCustomLevelHeadPrefix = new QCheckBox(QStringLiteral("LevelHead Prefix"));
    levelHeadText = new QLineEdit();
    levelHeadText->setPlaceholderText(QStringLiteral("Level: "));

    useCustomAutoggMessage = new QCheckBox(QStringLiteral("AutoGG Message"));
    autoggMessage = new QLineEdit();
    autoggMessage->setPlaceholderText(QStringLiteral("gg"));


    windowWidth = new QSpinBox();
    windowHeight = new QSpinBox();

    windowWidth->setMinimum(0);
    windowWidth->setMaximum(99999);

    windowHeight->setMinimum(0);
    windowHeight->setMaximum(99999);

    QHBoxLayout* windowResContainer = new QHBoxLayout();
    windowResContainer->setSpacing(30);
    windowResContainer->addWidget(new QLabel(QStringLiteral("Window Width")));
    windowResContainer->addWidget(windowWidth, 1);
    windowResContainer->addWidget(new QLabel(QStringLiteral("Window Height")));
    windowResContainer->addWidget(windowHeight, 1);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(40);
    mainLayout->addLayout(customMCPathContainer);
    mainLayout->addLayout(serverContainer);
    mainLayout->addLayout(windowResContainer);
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addLayout(WidgetUtils::createOptional(useCustomNickHiderName, nickHiderName));
    hLayout->addLayout(WidgetUtils::createOptional(useCustomLevelHeadPrefix, levelHeadText));
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(WidgetUtils::createOptional(useCustomAutoggMessage, autoggMessage));
    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

QString MinecraftPage::title() {
    return QStringLiteral("Minecraft");
}

QIcon MinecraftPage::icon() {
    return QIcon(":/res/icons/minecraft.svg");
}

void MinecraftPage::apply() {
    config.useCustomMinecraftDir = customMinecraftDir->isChecked();
    config.customMinecraftDir = minecraftPathChooser->getPath();

    config.joinServerOnLaunch = joinServerOnLaunch->isChecked();
    config.serverIp = serverToJoin->text();

    config.windowWidth = windowWidth->value();
    config.windowHeight = windowHeight->value();
}

void MinecraftPage::load() {
    customMinecraftDir->setChecked(config.useCustomMinecraftDir);
    minecraftPathChooser->setPath(config.customMinecraftDir);

    joinServerOnLaunch->setChecked(config.joinServerOnLaunch);
    serverToJoin->setText(config.serverIp);

    windowWidth->setValue(config.windowWidth);
    windowHeight->setValue(config.windowHeight);
}







