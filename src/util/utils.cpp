//
// Created by nils on 6/7/22.
//

#include "utils.h"

#include <QStringList>
#include <QDir>
#include <QVersionNumber>

#include "fs.h"

QString Utils::getAgentFlags(const QString &name) {
    return "-javaagent:" + FS::combinePaths(FS::getAgentsDirectory(), name);
}

QString Utils::getAgentFlags(const QString &name, const QString &option) {
    return getAgentFlags(name) + "=" + option;
}

QString Utils::getAssetsIndex(const QString &version) {
    if(version == "1.7")
        return "1.7.10";

    if(version.startsWith("1.18"))
        return "1.18";

    return version;
}


QStringList Utils::getOrderedAvailableVersions() {
    QString lunarDir = FS::getLunarDirectory();

    QDir jreDir(lunarDir + "/jre");

    QStringList list = jreDir.entryList({"1.*"}, QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    {
        QDir offlineDir(FS::combinePaths(lunarDir, "offline"));

        QMutableStringListIterator it(list);
        while(it.hasNext()){
            if(!offlineDir.exists(it.next())){
                it.remove();
            }
        }
    }

    std::sort(list.begin(), list.end(), [](const QString& a, const QString& b){
        return QVersionNumber::fromString(a) < QVersionNumber::fromString(b);
    });

    return list;
}