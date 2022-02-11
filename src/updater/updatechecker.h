//
// Created by nils on 2/8/22.
//

#ifndef LUNAR_CLIENT_QT_UPDATECHECKER_H
#define LUNAR_CLIENT_QT_UPDATECHECKER_H

#include <QObject>
#include <QNetworkAccessManager>

class UpdateChecker : public QObject {
Q_OBJECT
public:
    UpdateChecker();

    void checkForUpdates(bool emitIfUnavailable = true);
signals:
    void updateAvailable(const QString& url);
    void noUpdatesAvailable();
private slots:
    void parseApiResonse(QNetworkReply* reply);
private:
    QNetworkAccessManager networkManager;
};


#endif //LUNAR_CLIENT_QT_UPDATECHECKER_H
