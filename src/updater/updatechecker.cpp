//
// Created by nils on 2/8/22.
//

#include "updatechecker.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "buildconfig.h"

UpdateChecker::UpdateChecker() {
    connect(&networkManager, &QNetworkAccessManager::finished, this, &UpdateChecker::parseApiResonse);
}

void UpdateChecker::checkForUpdates(bool emitIfUnavailable) {
    QNetworkRequest request(BuildConfig::RELEASES_API_LINK);
    request.setAttribute(QNetworkRequest::User, emitIfUnavailable);

    networkManager.get(request);
}

void UpdateChecker::parseApiResonse(QNetworkReply *reply) {
    if(reply->error() != QNetworkReply::NoError){
        reply->deleteLater();
        return;
    }

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll(), &err);

    if(err.error != QJsonParseError::NoError){
        reply->deleteLater();
        return;
    }

    QJsonArray releases = doc.array();
    if(!releases.isEmpty()){
        QJsonObject obj = releases.first().toObject();
        if(obj["tag_name"].toString() != BuildConfig::VERSION_TAG){
            emit updateAvailable(obj["html_url"].toString());
        }else{
            bool shouldEmit = reply->request().attribute(QNetworkRequest::User).toBool();
            if(shouldEmit)
                emit noUpdatesAvailable();
        }
    }

    reply->deleteLater();
}
