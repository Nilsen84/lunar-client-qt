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

    saveObj["useLevelHeadPrefix"] = useLevelHeadPrefix;
    saveObj["levelHeadPrefix"] = levelHeadPrefix;

    saveObj["useAutoggMessage"] = useAutoggMessage;
    saveObj["autoggMessage"] = autoggMessage;

    saveObj["useNickLevel"] = useNickLevel;
    saveObj["nickLevel"] = nickLevel;

    saveObj["windowWidth"] = windowWidth;
    saveObj["windowHeight"] = windowHeight;


    QJsonArray arr;
    foreach(const Agent& agent, agents){
        QJsonObject agentObj;
        agentObj["path"] = agent.path;
        agentObj["option"] = agent.option;
        arr.append(agentObj);
    }

    saveObj["agents"] = arr;

    saveJsonToConfig(saveObj);
}

Config Config::load() {
    QJsonObject jsonObj = loadJsonFromFile();

    QJsonArray arr = jsonObj["agents"].toArray();

    QList<Agent> agents;

    foreach(const QJsonValue& val, arr){
        if(val.isObject()){
            QJsonObject obj = val.toObject();
            QString path = obj["path"].toString();
            if(QFile::exists(path)){
                agents.append({path, obj["option"].toString({})});
            }
        }else{
            QString path = val.toString();
            agents.append({path, {}});
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
        jsonObj["useLevelHeadPrefix"].toBool(false),
        jsonObj["levelHeadPrefix"].toString(),
        jsonObj["useAutoggMessage"].toBool(false),
        jsonObj["autoggMessage"].toString(),
        jsonObj["useNickLevel"].toBool(true),
        jsonObj["nickLevel"].toInt(-1),
        jsonObj["windowWidth"].toInt(640),
        jsonObj["windowHeight"].toInt(480),
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
