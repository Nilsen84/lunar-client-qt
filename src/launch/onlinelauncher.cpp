//
// Created by nils on 11/27/21.
//

#include "onlinelauncher.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSysInfo>


OnlineLauncher::OnlineLauncher(QObject *parent) : Launcher(parent) {
    connect(&launchRequestManager, &QNetworkAccessManager::finished, this, &OnlineLauncher::parseLaunchData);
}

void OnlineLauncher::launch(const Launcher::LaunchOptions &launchOptions) {
    sendLaunchDataRequest(launchOptions.version);
}

void OnlineLauncher::sendLaunchDataRequest(const QString& version) {
    QNetworkRequest postReq(QUrl(QStringLiteral("https://api.lunarclientprod.com/launcher/launch")));
    postReq.setHeader(QNetworkRequest::UserAgentHeader, "Lunar Client Launcher v2.8.8");

    QJsonObject postData;
    postData[QStringLiteral("hwid")] = "amogus";
    postData[QStringLiteral("os")] = getCurrentOs();
    postData[QStringLiteral("arch")] = getCurrentArchitecture();
    postData[QStringLiteral("launcher_version")] = "2.8.8";
    postData[QStringLiteral("version")] = version;
    postData[QStringLiteral("branch")] = "master";
    postData[QStringLiteral("launch_type")] = "OFFLINE";
    postData[QStringLiteral("classifier")] = "optifine";

    launchRequestManager.post(postReq, QJsonDocument(postData).toJson());
}

void OnlineLauncher::parseLaunchData(QNetworkReply* reply) {
    qDebug() << "amogus";
    qDebug() << reply->readAll();
    qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

QString OnlineLauncher::getCurrentOs() {
    QString kernel = QSysInfo::kernelType();

    if(kernel == QStringLiteral("winnt"))
        return QStringLiteral("win32");
    return kernel;
}

QString OnlineLauncher::getCurrentArchitecture() {
    QString arch = QSysInfo::currentCpuArchitecture();

    if(arch == QStringLiteral("x86_64"))
        return QStringLiteral("x64");
    return arch;
}


