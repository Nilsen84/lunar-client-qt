//
// Created by nils on 11/4/21.
//

#include "offlinelauncher.h"

#include <QProcess>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>
#include <QTemporaryFile>
#include <QElapsedTimer>

#include "util/fs.h"
#include "util/utils.h"

OfflineLauncher::OfflineLauncher(const Config& config, QObject *parent) : Launcher(config, parent) {
}


bool OfflineLauncher::launch(CosmeticsState cosmeticsState) {
    if(config.gameVersion.isEmpty()){
        emit error("No version selected!\nDo you have lunar installed?");
        return false;
    }

    QProcess process;
    process.setProgram(config.useCustomJre ? config.customJrePath : findJavaExecutable(config.gameVersion));

    process.setStandardInputFile(QProcess::nullDevice());
    process.setStandardOutputFile(QProcess::nullDevice());
    process.setStandardErrorFile(QProcess::nullDevice());

    QString workingDir = FS::combinePaths(
            FS::lunarDirectory(),
        "offline",
        config.gameVersion
    );

    process.setWorkingDirectory(workingDir);

    QStringList classPath = QDir(workingDir).entryList(QDir::Files, QDir::Time);

    QFileInfoList libsList = QDir(FS::libsDirectory()).entryInfoList(QDir::Files);

    for(const QFileInfo& info : libsList) {
        classPath << info.absoluteFilePath();
    }

    QStringList args{
         "--add-modules", "jdk.naming.dns",
         "--add-exports", "jdk.naming.dns/com.sun.jndi.dns=java.naming",
         "-Djna.boot.library.path=natives",
         "-Dlog4j2.formatMsgNoLookups=true",
         "--add-opens", "java.base/java.io=ALL-UNNAMED",
         QString("-Xms%1m").arg(config.initialMemory),
         QString("-Xmx%1m").arg(config.maximumMemory),
         "-Djava.library.path=natives",
         "-cp", classPath.join(QDir::listSeparator())
    };

    for(const Agent& agent : config.agents)
        if(agent.enabled)
            args << "-javaagent:" + agent.path + '=' + agent.option;


    if(config.useLevelHeadPrefix)
        args << Utils::getAgentFlags("CustomLevelHead", config.levelHeadPrefix);

    if(config.useAutoggMessage)
        args << Utils::getAgentFlags("CustomAutoGG", config.autoggMessage);

    if(config.useNickLevel)
        args << Utils::getAgentFlags("NickLevel", QString::number(config.nickLevel));

    if(cosmeticsState == CosmeticsState::UNLOCKED)
        args << Utils::getAgentFlags("UnlockCosmetics");

    args << QProcess::splitCommand(config.jvmArgs);

    args << QStringList{
            "com.moonsworth.lunar.patcher.LunarMain",
            "--version", config.gameVersion,
            "--accessToken", "0",
            "--assetIndex", Utils::getAssetsIndex(config.gameVersion),
            "--userProperties", "{}",
            "--gameDir", config.useCustomMinecraftDir ? config.customMinecraftDir : FS::minecraftDirectory(),
            "--launcherVersion", "2.10.0",
            "--width", QString::number(config.windowWidth),
            "--height", QString::number(config.windowHeight)
    };

    if(cosmeticsState != CosmeticsState::OFF)
        args << "--texturesDir" << FS::combinePaths(FS::lunarDirectory(), "textures");

    if(config.joinServerOnLaunch)
        args << "--server" << config.serverIp;

    process.setArguments(args);

    //Removes the windir environment variable, preventing lunar from reading your hosts file and executing tasklist on windows

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.remove("windir");

    process.setProcessEnvironment(env);

    if(!process.startDetached()){
        emit error("Failed to start process: " + process.errorString());
        return false;
    }

    return true;
}

QString OfflineLauncher::findJavaExecutable(const QString& version) {
    QString jreDir = FS::combinePaths(FS::lunarDirectory(), "jre");

    QDirIterator jreIt(FS::combinePaths(jreDir, version), QDir::Dirs | QDir::NoDotAndDotDot);

    while(jreIt.hasNext()){
        QString potentialExecutable = FS::combinePaths(
                jreIt.next(),
                "bin",
#ifdef Q_OS_WIN
                "javaw.exe"
#else
                "java"
#endif

        );

        if(QFileInfo(potentialExecutable).isExecutable())
            return potentialExecutable;
    }

    return {};
}
