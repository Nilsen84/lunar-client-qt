//
// Created by nils on 12/1/21.
//

#include "config.h"

#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QJsonDocument>

const QString Config::configFilePath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/lunar-client-qt/config.json";

void Config::save() {
    QJsonObject saveObj;

    saveObj["version"] = gameVersion;

    saveObj["keepMemorySame"] = keepMemorySame;
    saveObj["initialMemory"] = initialMemory;
    saveObj["maxMemory"] = maximumMemory;

    saveObj["windowWidth"] = windowWidth;
    saveObj["windowHeight"] = windowHeight;

    saveObj["useCustomJre"] = useCustomJre;
    saveObj["customJrePath"] = customJrePath;

    saveObj["jvmArgs"] = jvmArgs;


    QJsonArray arr;
    for(const QString& str : agents)
        arr.append(str);

    saveObj["agents"] = arr;

    saveJsonToConfig(saveObj);
}

Config Config::load() {
    QJsonObject jsonObj = loadJsonFromFile();

    QJsonArray arr = jsonObj["agents"].toArray();

    QStringList agents;

    for(auto val : arr){
        QString path = val.toString();
        if(QFile::exists(path)){
            agents.append(path);
        }
    }

    return {
        jsonObj["version"].toInt(1),
        jsonObj["keepMemorySame"].toBool(true),
        jsonObj["initialMemory"].toInt(4096),
        jsonObj["maxMemory"].toInt(4096),
        jsonObj["windowWidth"].toInt(640),
        jsonObj["windowHeight"].toInt(480),
        jsonObj["useCustomJre"].toBool(false),
        jsonObj["customJrePath"].toString(),
        jsonObj["jvmArgs"].toString(),
        agents
    };
}

void Config::saveJsonToConfig(const QJsonObject &jsonObject) {
    QString path = QFileInfo(configFilePath).absolutePath();
    QDir dir;
    if(!dir.exists(path)){
        dir.mkdir(path);
    }

    QFile configFile(configFilePath);

    configFile.open(QIODevice::WriteOnly);

    configFile.write(QJsonDocument(jsonObject).toJson());

    configFile.close();
}

QJsonObject Config::loadJsonFromFile() {
    QFile configFile(configFilePath);
    configFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonObject jsonObj = QJsonDocument::fromJson(configFile.readAll()).object();

    configFile.close();

    return jsonObj;
}
