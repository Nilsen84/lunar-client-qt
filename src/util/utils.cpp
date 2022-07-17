//
// Created by nils on 6/7/22.
//

#include "utils.h"

#include <QStringList>
#include <QDir>
#include <QVersionNumber>
#include <QDirIterator>

#include "fs.h"

QString Utils::getAgentFlags(const QString &name) {
    return "-javaagent:" + FS::combinePaths(FS::agentsDirectory(), name);
}

QString Utils::getAgentFlags(const QString &name, const QString &option) {
    return getAgentFlags(name) + "=" + option;
}

QString Utils::getAssetsIndex(const QString &version) {
    auto split = version.split('.');

    if (split.length() < 2) {
        return version;
    }

    return split[0] + '.' + split[1];
}

void Utils::sortVersions(QStringList &versions) {
    std::sort(versions.begin(), versions.end(), [](const QString& a, const QString& b){
        return QVersionNumber::fromString(a) < QVersionNumber::fromString(b);
    });
}

QStringList Utils::getAvailableVersions() {
    QDirIterator dirIt(
            FS::combinePaths(
                    FS::lunarDirectory(),
                    "offline",
                    "multiver"
            ),
            QDir::Files
    );

    QStringList versions;

    while(dirIt.hasNext()){
        dirIt.next();
        auto name = dirIt.fileInfo().baseName();
        auto split = name.split('-');
        if(split.isEmpty()) continue;

        auto version = split.last();

        if(version.startsWith("v1_")){
            versions << dotVersion(version);
        }
    }

    return versions;
}

QStringList Utils::getOrderedAvailableVersions() {
    auto versions = getAvailableVersions();
    sortVersions(versions);
    return versions;
}

QString Utils::underscoreVersion(const QString &version) {
    return 'v' + QString(version).replace('.', '_');
}

QString Utils::dotVersion(const QString &underscoreVersion) {
    return underscoreVersion.mid(1).replace('_', '.');
}