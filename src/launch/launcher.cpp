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
