//
// Created by nils on 6/7/22.
//

#ifndef LUNAR_CLIENT_QT_UTILS_H
#define LUNAR_CLIENT_QT_UTILS_H


#include <QString>

namespace Utils {
    QString getAgentFlags(const QString& name);
    QString getAgentFlags(const QString& name, const QString& option);
    QString getAssetsIndex(const QString& version);

    void sortVersions(QStringList& versions);
    QStringList getAvailableVersions();
    QStringList getOrderedAvailableVersions();

    QString underscoreVersion(const QString& version);
    QString dotVersion(const QString& underscoreVersion);
};


#endif //LUNAR_CLIENT_QT_UTILS_H
