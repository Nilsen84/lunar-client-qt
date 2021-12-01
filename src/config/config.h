//
// Created by nils on 12/1/21.
//

#ifndef LUNAR_CLIENT_QT_CONFIG_H
#define LUNAR_CLIENT_QT_CONFIG_H

#include <QString>
#include <QStringList>
#include <QJsonObject>

class Config {
public:
    int gameVersion;


    bool keepMemorySame;
    int initialMemory;
    int maximumMemory;

    int windowWidth;

    int windowHeight;

    bool useCustomJre;
    QString customJrePath;

    QString jvmArgs;


    QStringList agents;
public:
    void save();
    static Config load();
private:
    static void saveJsonToConfig(const QJsonObject& jsonObject);
    static QJsonObject loadJsonFromFile();


    Config() = default;

    static const QString configFilePath;
};


#endif //LUNAR_CLIENT_QT_CONFIG_H
