//
// Created by nils on 12/2/21.
//

#include "minecraftpage.h"

#include <QHBoxLayout>
#include <QLabel>
#include <limits>

#include <gui/widgets/widgetutils.h>

MinecraftPage::MinecraftPage(Config &config, QWidget *parent) : ConfigurationPage(config, parent) {
    customMinecraftDir = new QCheckBox(QStringLiteral("Custom .minecraft Directory"));
    minecraftPathChooser = new FileChooser(QFileDialog::Directory);

    serverToJoin = new QLineEdit();
    serverToJoin->setDisabled(true);

    connect(serverToJoin, &QLineEdit::returnPressed, [this](){serverToJoin->clearFocus();});

    joinServerOnLaunch = new QCheckBox(QStringLiteral("Join Server On Launch"));

    connect(joinServerOnLaunch, &QCheckBox::toggled, serverToJoin, &QLineEdit::setEnabled);

    QVBoxLayout* serverContainer = new QVBoxLayout();
    serverContainer->setSpacing(6);
    serverContainer->addWidget(joinServerOnLaunch, 0, Qt::AlignHCenter);
    serverContainer->addWidget(serverToJoin);

    useLevelHeadPrefix = new QCheckBox(QStringLiteral("LevelHead Prefix"));
    levelHeadPrefix = new QLineEdit();
    levelHeadPrefix->setPlaceholderText(QStringLiteral("Level: "));

    useAutoggMessage = new QCheckBox(QStringLiteral("AutoGG Message"));
    autoggMessage = new QLineEdit();
    autoggMessage->setPlaceholderText(QStringLiteral("gg"));

    useNickLevel = new QCheckBox(QStringLiteral("LevelHead level shown for nicks (-1 means nothing will show)"));
    nickLevel = new QSpinBox;
    nickLevel->setMinimum(INT_MIN);
    nickLevel->setMaximum(INT_MAX);

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
    mainLayout->addLayout(WidgetUtils::createOptional(customMinecraftDir, minecraftPathChooser));
    mainLayout->addLayout(serverContainer);
    mainLayout->addLayout(windowResContainer);
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addLayout(WidgetUtils::createOptional(useLevelHeadPrefix, levelHeadPrefix));
    hLayout->addLayout(WidgetUtils::createOptional(useAutoggMessage, autoggMessage));

    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(WidgetUtils::createOptional(useNickLevel, nickLevel));

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

    config.useLevelHeadPrefix = useLevelHeadPrefix->isChecked();
    config.levelHeadPrefix = levelHeadPrefix->text();

    config.useAutoggMessage = useAutoggMessage->isChecked();
    config.autoggMessage = autoggMessage->text();

    config.useNickLevel = useNickLevel->isChecked();
    config.nickLevel = nickLevel->value();

    config.windowWidth = windowWidth->value();
    config.windowHeight = windowHeight->value();
}

void MinecraftPage::load() {
    customMinecraftDir->setChecked(config.useCustomMinecraftDir);
    minecraftPathChooser->setPath(config.customMinecraftDir);

    joinServerOnLaunch->setChecked(config.joinServerOnLaunch);
    serverToJoin->setText(config.serverIp);

    useLevelHeadPrefix->setChecked(config.useLevelHeadPrefix);
    levelHeadPrefix->setText(config.levelHeadPrefix);

    useAutoggMessage->setChecked(config.useAutoggMessage);
    autoggMessage->setText(config.autoggMessage);

    useNickLevel->setChecked(config.useNickLevel);
    nickLevel->setValue(config.nickLevel);

    windowWidth->setValue(config.windowWidth);
    windowHeight->setValue(config.windowHeight);
}

QString MinecraftPage::description() {
    return "Minecraft settings.";
}







