//
// Created by nils on 2/3/22.
//

#ifndef LUNAR_CLIENT_QT_UTILS_H
#define LUNAR_CLIENT_QT_UTILS_H

#include <QString>

namespace Utils {
    QString getLibsDirectory();
    QString getAgentsDirectory();


    QString getAgentFlags(const QString& name);
    QString getAgentFlags(const QString& name, const QString& option);

    QString getAssetsIndex(const QString& version);
}


#endif //LUNAR_CLIENT_QT_UTILS_H
