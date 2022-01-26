//
// Created by nils on 11/27/21.
//

#include "launcher.h"

Launcher::Launcher(const Config& config, QObject *parent) : config(config), QObject(parent) {
}

QString Launcher::getAgentFlags(const QString &path, const QString &options) {
    return QStringLiteral("-javaagent:%1=%2")
        .arg(path,  options);
}

QString Launcher::getLevelHeadOptions(const bool& uselevelheadprefix, const QString& levelheadprefix, const bool& uselevelheadnicklevel, const QString& levelheadnicklevel) {
    if (!uselevelheadprefix && uselevelheadnicklevel)
        return QStringLiteral("@") + levelheadnicklevel;
    else if (!uselevelheadnicklevel && uselevelheadprefix)
        return levelheadnicklevel;
    else return levelheadprefix + "@" + levelheadnicklevel;
};
