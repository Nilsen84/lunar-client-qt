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
    explicit OfflineLauncher(QObject* parent = nullptr);

    void launch(const LaunchOptions& launchOptions) override;
signals:
    void error(const QString& message);
private:
    static QString findJavaExecutable();
private:
    const static QString lunarDir;
    const static QString minecraftDir;
};


#endif //LUNAR_CLIENT_QT_OFFLINELAUNCHER_H
