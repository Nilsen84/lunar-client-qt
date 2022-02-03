//
// Created by nils on 2/3/22.
//

#include "utils.h"

#include <QDir>
#include <QApplication>

QString Utils::getLibsDirectory() {
    return QDir::cleanPath(QApplication::applicationDirPath() + QDir::separator() + "libs");
}

QString Utils::getAgentsDirectory() {
    return QDir::cleanPath(QApplication::applicationDirPath() + QDir::separator() + "agents");
}

QString Utils::getAgentFlags(const QString &name) {
    return QStringLiteral("-javaagent:") + getAgentsDirectory() + QDir::separator() + name;
}

QString Utils::getAgentFlags(const QString &name, const QString &option) {
    return getAgentFlags(name) + "=" + option;
}