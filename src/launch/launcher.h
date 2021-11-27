//
// Created by nils on 11/27/21.
//

#ifndef LUNAR_CLIENT_QT_LAUNCHER_H
#define LUNAR_CLIENT_QT_LAUNCHER_H

#include <QObject>

class Launcher : public QObject {
Q_OBJECT
public:
    explicit Launcher(QObject* parent);

    struct LaunchOptions{
        QString version = QStringLiteral("1.8");
        bool findLunarJre = true;
        QString customJre;
        QString jvmArgs;
        QStringList agents;
        int initialMem = 4096;
        int maxMem = 4096;
        int windowWidth = 640;
        int windowHeight = 480;
    };

    virtual void launch(const LaunchOptions& launchOptions) = 0;
};

#endif //LUNAR_CLIENT_QT_LAUNCHER_H
