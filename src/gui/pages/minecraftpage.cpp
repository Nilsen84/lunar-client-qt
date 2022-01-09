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

    serverToJoin = new QLineEdit();
    serverToJoin->setDisabled(true);

    connect(serverToJoin, &QLineEdit::returnPressed, [this](){serverToJoin->clearFocus();});

    joinServerOnLaunch = new QCheckBox(QStringLiteral("Join Server On Launch"));

    connect(joinServerOnLaunch, &QCheckBox::toggled, serverToJoin, &QLineEdit::setEnabled);

    QVBoxLayout* serverContainer = new QVBoxLayout();
    serverContainer->setSpacing(6);
    serverContainer->addWidget(joinServerOnLaunch, 0, Qt::AlignHCenter);
    serverContainer->addWidget(serverToJoin);

    useNickHiderName = new QCheckBox(QStringLiteral("NickHider Name"));
    nickHiderName = new QLineEdit();
    nickHiderName->setPlaceholderText(QStringLiteral("You"));

    useLevelHeadPrefix = new QCheckBox(QStringLiteral("LevelHead Prefix"));
    levelHeadPrefix = new QLineEdit();
    levelHeadPrefix->setPlaceholderText(QStringLiteral("Level: "));

    useAutoggMessage = new QCheckBox(QStringLiteral("AutoGG Message"));
    autoggMessage = new QLineEdit();
    autoggMessage->setPlaceholderText(QStringLiteral("gg"));

    useCosmetics = new QCheckBox(QStringLiteral("Enable Cosmetics"));
    unlockCosmetics = new QCheckBox(QStringLiteral("Unlock All Cosmetics"));

    connect(useCosmetics, &QCheckBox::toggled, unlockCosmetics, &QCheckBox::setEnabled);

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
    hLayout->addLayout(WidgetUtils::createOptional(useNickHiderName, nickHiderName));
    hLayout->addLayout(WidgetUtils::createOptional(useLevelHeadPrefix, levelHeadPrefix));
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(WidgetUtils::createOptional(useAutoggMessage, autoggMessage));
    mainLayout->addWidget(useCosmetics, 1, Qt::AlignHCenter);
    mainLayout->addWidget(unlockCosmetics, 0, Qt::AlignCenter);
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

    config.useNickHiderName = useNickHiderName->isChecked();
    config.nickHiderName = nickHiderName->text();

    config.useLevelHeadPrefix = useLevelHeadPrefix->isChecked();
    config.levelHeadPrefix = levelHeadPrefix->text();

    config.useAutoggMessage = useAutoggMessage->isChecked();
    config.autoggMessage = autoggMessage->text();

    config.useCosmetics = useCosmetics->isChecked();
    config.unlockCosmetics = unlockCosmetics->isChecked();

    config.windowWidth = windowWidth->value();
    config.windowHeight = windowHeight->value();
}

void MinecraftPage::load() {
    customMinecraftDir->setChecked(config.useCustomMinecraftDir);
    minecraftPathChooser->setPath(config.customMinecraftDir);

    joinServerOnLaunch->setChecked(config.joinServerOnLaunch);
    serverToJoin->setText(config.serverIp);

    useNickHiderName->setChecked(config.useNickHiderName);
    nickHiderName->setText(config.nickHiderName);

    useLevelHeadPrefix->setChecked(config.useLevelHeadPrefix);
    levelHeadPrefix->setText(config.levelHeadPrefix);

    useAutoggMessage->setChecked(config.useAutoggMessage);
    autoggMessage->setText(config.autoggMessage);

    useCosmetics->setChecked(config.useCosmetics);
    unlockCosmetics->setChecked(config.unlockCosmetics);

    windowWidth->setValue(config.windowWidth);
    windowHeight->setValue(config.windowHeight);
}