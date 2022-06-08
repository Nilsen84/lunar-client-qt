//
// Created by nils on 6/7/22.
//

#include "fs.h"

#include <QDir>
#include <QApplication>
#include <QStandardPaths>

#include "buildconfig.h"


QString FS::combinePaths(const QString &a, const QString &b) {
    return QDir::cleanPath(a + QDir::separator() + b);
}

QString FS::combinePaths(const QString &a, const QString &b, const QString &c) {
    return combinePaths(combinePaths(a, b), c);
}



QString FS::getLibsDirectory() {
    return combinePaths(QApplication::applicationDirPath(), BuildConfig::LIBS_DIR);
}

QString FS::getAgentsDirectory() {
    return combinePaths(QApplication::applicationDirPath(), BuildConfig::AGENTS_DIR);
}

QString FS::getLunarDirectory() {
    return combinePaths(QDir::homePath(), ".lunarclient");
}

QString FS::getMinecraftDirectory() {
    return combinePaths(
            QDir::homePath(),

#if defined(Q_OS_WIN)
            "AppData/Roaming/.minecraft"
#elif defined(Q_OS_DARWIN)
            "Library/Application Support/minecraft"
#else
            ".minecraft"
#endif
    );
}
