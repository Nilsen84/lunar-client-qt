//
// Created by nils on 6/7/22.
//

#include "fs.h"

#include <QDir>
#include <QApplication>
#include <QStandardPaths>

#include "buildconfig.h"


QString FS::combinePaths(const QString &a, const QString &b) {
    return a + QDir::separator() + b;
}

QString FS::combinePaths(const QString &a, const QString &b, const QString &c) {
    return combinePaths(combinePaths(a, b), c);
}

QString FS::agentsDirectory() {
    return combinePaths(QApplication::applicationDirPath(), BuildConfig::AGENTS_DIR);
}

QString FS::lunarDirectory() {
    return combinePaths(QDir::homePath(), ".lunarclient");
}

QString FS::minecraftDirectory() {
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

bool FS::clearDirectory(const QString &dir) {
    QDir qdir(dir);
    for(const auto& file : qdir.entryList(QDir::Files))
        if(!qdir.remove(file))
            return false;
    return true;
}
