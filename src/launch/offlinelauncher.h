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

    bool launch(CosmeticsState cosmeticsState) override;
signals:
    void error(const QString& message);
private:
    struct LaunchFiles {
        QStringList classPath;
        QStringList externalFiles;
        QString natives;
    };

    LaunchFiles gatherLaunchFiles(const QString& workingDir);

    QString findJavaExecutable();
};


#endif //LUNAR_CLIENT_QT_OFFLINELAUNCHER_H
