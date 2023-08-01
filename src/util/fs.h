//
// Created by nils on 6/7/22.
//

#ifndef LUNAR_CLIENT_QT_FS_H
#define LUNAR_CLIENT_QT_FS_H

#include <QString>

namespace FS {
    QString combinePaths(const QString& a, const QString& b);
    QString combinePaths(const QString& a, const QString& b, const QString& c);

    QString agentsDirectory();

    QString lunarDirectory();
    QString minecraftDirectory();

    bool clearDirectory(const QString& dir);
};


#endif //LUNAR_CLIENT_QT_FS_H
