//
// Created by nils on 12/1/21.
//

#include "config.h"

#include <QStandardPaths>
#include <QJsonObject>
#include <QProcess>
#include <QJsonArray>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QJsonDocument>

const QString Config::configFilePath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/lunar-client-qt/settings.json";

void Config::save() {
    QJsonObject saveObj;

    saveObj["version"] = gameVersion;

    saveObj["keepMemorySame"] = keepMemorySame;
    saveObj["initialMemory"] = initialMemory;
    saveObj["maxMemory"] = maximumMemory;

    saveObj["useCustomJre"] = useCustomJre;
    saveObj["customJrePath"] = customJrePath;

    saveObj["closeOnLaunch"] = closeOnLaunch;

    saveObj["jvmArgs"] = jvmArgs;

    saveObj["useCustomMinecraftDir"] = useCustomMinecraftDir;
    saveObj["customMinecraftDir"] = customMinecraftDir;

    saveObj["joinServerOnLaunch"] = joinServerOnLaunch;
    saveObj["serverIp"] = serverIp;

    saveObj["useNickHiderName"] = useNickHiderName;
    saveObj["nickHiderName"] = nickHiderName;

    saveObj["useLevelHeadPrefix"] = useLevelHeadPrefix;
    saveObj["levelHeadPrefix"] = levelHeadPrefix;

    saveObj["useAutoggMessage"] = useAutoggMessage;
    saveObj["autoggMessage"] = autoggMessage;

    saveObj["useCosmetics"] = useCosmetics;
    saveObj["unlockCosmetics"] = unlockCosmetics;

    saveObj["windowWidth"] = windowWidth;
    saveObj["windowHeight"] = windowHeight;

    QJsonArray arr;
    foreach(const QString& str, agents){
        arr.append(str);
    }

    saveObj["agents"] = arr;

    saveJsonToConfig(saveObj);
}

Config Config::load() {
    QJsonObject jsonObj = loadJsonFromFile();

    QJsonArray arr = jsonObj["agents"].toArray();

    QStringList agents;

    foreach(const QJsonValue& val, arr){
        QString path = val.toString();
        if(QFile::exists(path)){
            agents.append(path);
        }
    }


    return {
        jsonObj["version"].toString("1.8"),
        jsonObj["keepMemorySame"].toBool(true),
        jsonObj["initialMemory"].toInt(4096),
        jsonObj["maxMemory"].toInt(4096),
        jsonObj["useCustomJre"].toBool(false),
        jsonObj["customJrePath"].toString(),
        jsonObj["jvmArgs"].toString(),
        jsonObj["closeOnLaunch"].toBool(false),
        jsonObj["useCustomMinecraftDir"].toBool(false),
        jsonObj["customMinecraftDir"].toString(),
        jsonObj["joinServerOnLaunch"].toBool(false),
        jsonObj["serverIp"].toString(),
        jsonObj["useNickHiderName"].toBool(false),
        jsonObj["nickHiderName"].toString(),
        jsonObj["useLevelHeadPrefix"].toBool(false),
        jsonObj["levelHeadPrefix"].toString(),
        jsonObj["useAutoggMessage"].toBool(false),
        jsonObj["autoggMessage"].toString(),
        jsonObj["windowWidth"].toInt(640),
        jsonObj["windowHeight"].toInt(480),
        jsonObj["useCosmetics"].toBool(true),
        jsonObj["unlockCosmetics"].toBool(false),
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
