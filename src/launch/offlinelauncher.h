//
// Created by nils on 11/4/21.
//

#ifndef LUNAR_CLIENT_QT_OFFLINELAUNCHER_H
#define LUNAR_CLIENT_QT_OFFLINELAUNCHER_H

#include <QObject>

#include "launcher.h"


class OfflineLauncher : public Launcher{
Q_OBJECT
public:
    explicit OfflineLauncher(const Config& config, QObject* parent = nullptr);

    void launch();
signals:
    void error(const QString& message);
private:
    static QString findJavaExecutable(const QString& version);
    static void HelperLaunch(const QString& helper);
private:
    const static QString lunarDir;
    const static QString minecraftDir;
};


#endif //LUNAR_CLIENT_QT_OFFLINELAUNCHER_H
