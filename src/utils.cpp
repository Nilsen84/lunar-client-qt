//
// Created by nils on 2/3/22.
//

#include "utils.h"

#include <QDir>
#include <QApplication>

#include "buildconfig.h"

QString Utils::getLibsDirectory() {
    return QDir::cleanPath(QApplication::applicationDirPath() + QDir::separator() + BuildConfig::LIBS_DIR);
}

QString Utils::getAgentsDirectory() {
    return QDir::cleanPath(QApplication::applicationDirPath() + QDir::separator() + BuildConfig::AGENTS_DIR);
}

QString Utils::getAgentFlags(const QString &name) {
    return QStringLiteral("-javaagent:") + getAgentsDirectory() + QDir::separator() + name;
}

QString Utils::getAgentFlags(const QString &name, const QString &option) {
    return getAgentFlags(name) + "=" + option;
}