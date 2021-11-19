//
// Created by nils on 11/4/21.
//

#ifndef LUNAR_CLIENT_QT_LAUNCHER_H
#define LUNAR_CLIENT_QT_LAUNCHER_H

#include <QObject>

class Launcher : public QObject{
Q_OBJECT
public:
    struct LaunchData{
        QString version = QStringLiteral("1.8");
        bool findLunarJre = true;
        QString customJre;
        int initialMem = 4096;
        int maxMem = 4096;
        int windowWidth = 640;
        int windowHeight = 480;
    };
    explicit Launcher(QObject* parent = nullptr);

    void launch(bool offline, const LaunchData& launchData);

signals:
    void finished();
private:
    static QString findJavaExecutable();
private:
    const static QString lunarDir;
    const static QString minecraftDir;
};


#endif //LUNAR_CLIENT_QT_LAUNCHER_H
