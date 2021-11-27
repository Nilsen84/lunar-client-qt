//
// Created by nils on 11/27/21.
//

#ifndef LUNAR_CLIENT_QT_ONLINELAUNCHER_H
#define LUNAR_CLIENT_QT_ONLINELAUNCHER_H

#include <QNetworkAccessManager>

#include "launcher.h"

class OnlineLauncher : public Launcher {
Q_OBJECT
public:
    explicit OnlineLauncher(QObject* parent = nullptr);

    void launch(const LaunchOptions& launchOptions) override;

signals:
    void launchUpdate(const QString& message);
    void launchFinished();
private slots:
     void parseLaunchData(QNetworkReply* reply);
signals:

private:
    struct LaunchData {

    };
private:
    void sendLaunchDataRequest(const QString& version);
    void updateCosmetics(const LaunchData& launchData);
    void updateArtifacts(const LaunchData& launchData);

    QString getCurrentOs();
    QString getCurrentArchitecture();

    QNetworkAccessManager launchRequestManager;
};


#endif //LUNAR_CLIENT_QT_ONLINELAUNCHER_H
