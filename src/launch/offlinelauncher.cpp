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
#include <QVersionNumber>
#include <quazip.h>
#include <JlCompress.h>

#include "util/fs.h"
#include "util/utils.h"

OfflineLauncher::OfflineLauncher(const Config &config, QObject *parent) : Launcher(config, parent) {
}

OfflineLauncher::LaunchFiles OfflineLauncher::gatherLaunchFiles(const QString& workingDir){
    LaunchFiles launchFiles;

    QDirIterator dirIt(workingDir, QDir::Files);

    auto version = Utils::underscoreVersion(config.gameVersion);

    while(dirIt.hasNext()){
        auto path = dirIt.next();
        auto name = dirIt.fileName();

        if(!name.contains(version) && name.contains("v1_"))
            continue;

        if(name.startsWith("OptiFine")){
            launchFiles.externalFiles << path;
        }else if(name.endsWith(".zip") && name.contains("natives")){
            launchFiles.natives = path;
        }else {
            launchFiles.classPath << path;
        }
    }

    return launchFiles;
}

bool OfflineLauncher::launch(CosmeticsState cosmeticsState) {
    if (config.gameVersion.isEmpty()) {
        emit error("No version selected!\nDo you have lunar installed?");
        return false;
    }

    QProcess process;
    process.setProgram(config.useCustomJre ? config.customJrePath : findJavaExecutable());

    QString workingDir = FS::combinePaths(
        FS::lunarDirectory(),
        "offline",
        "multiver"
    );

    process.setWorkingDirectory(workingDir);

    QString natives = FS::combinePaths(workingDir, "natives");
    FS::clearDirectory(natives);

    auto [cp, externalFiles, nativesZip] = gatherLaunchFiles(workingDir);

    QuaZip zip(nativesZip);
    JlCompress::extractDir(zip, natives);


    QStringList args{
            "--add-modules", "jdk.naming.dns",
            "--add-exports", "jdk.naming.dns/com.sun.jndi.dns=java.naming",
            "-Djna.boot.library.path=natives",
            "-Dlog4j2.formatMsgNoLookups=true",
            "--add-opens", "java.base/java.io=ALL-UNNAMED",
            QString("-Xms%1m").arg(config.initialMemory),
            QString("-Xmx%1m").arg(config.maximumMemory),
            "-Djava.library.path=natives",
            "-cp", cp.join(QDir::listSeparator())
    };

    for (const Agent &agent: config.agents)
        if (agent.enabled)
            args << "-javaagent:" + agent.path + '=' + agent.option;

    if (cosmeticsState == CosmeticsState::UNLOCKED)
        args << Utils::getAgentFlags("UnlockCosmetics");

    args << QProcess::splitCommand(config.jvmArgs);

    args << QStringList{
            "com.moonsworth.lunar.genesis.Genesis",
            "--version", config.gameVersion,
            "--accessToken", "0",
            "--assetIndex", Utils::getAssetsIndex(config.gameVersion),
            "--userProperties", "{}",
            "--gameDir", config.useCustomMinecraftDir ? config.customMinecraftDir : FS::minecraftDirectory(),
            "--launcherVersion", "2.12.7",
            "--width", QString::number(config.windowWidth),
            "--height", QString::number(config.windowHeight),
            "--workingDirectory", ".",
            "--classpathDir", ".",
            "--ichorClassPath", cp.join(','),
            "--ichorExternalFiles", externalFiles.join(',')
    };

    if (cosmeticsState != CosmeticsState::OFF)
        args << "--texturesDir" << FS::combinePaths(FS::lunarDirectory(), "textures");

    if (config.joinServerOnLaunch)
        args << "--server" << config.serverIp;

    process.setArguments(args);

    //Removes the windir environment variable, preventing lunar from reading your hosts file and executing tasklist on windows

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.remove("windir");

    process.setProcessEnvironment(env);

    if (!process.startDetached()) {
        emit error("Failed to start process: " + process.errorString());
        return false;
    }

    return true;
}

struct JavaExe {
    QVersionNumber version;
    QString exe;
};

QVersionNumber getJreVersion(const QString& jreDirectoryName){
    auto split = jreDirectoryName.split('-');

    for(const auto& str : split){
        if(str.startsWith("jre") || str.startsWith("jdk")){
            return QVersionNumber::fromString(str.mid(3));
        }
    }

    return {0};
}

QList<JavaExe> getAvailableJres(){
    QList<JavaExe> jres;

    QDirIterator topIt(FS::combinePaths(FS::lunarDirectory(), "jre"), QDir::Dirs);
    while(topIt.hasNext()){
        auto next = topIt.next();

        QDirIterator jreIt(next, QDir::Dirs);
        while(jreIt.hasNext()){
            QString potentialExe = FS::combinePaths(
                    jreIt.next(),
                    "bin",
#ifdef Q_OS_WIN
                    "javaw.exe",
#else
                    "java"
#endif
            );

            if(QFileInfo(potentialExe).isExecutable()){
                jres.append({getJreVersion(jreIt.fileName()), potentialExe});
            }
        }
    }

    return jres;
}

QString OfflineLauncher::findJavaExecutable() {
    auto jres = getAvailableJres();
    if(jres.isEmpty()) return {};

    std::sort(jres.begin(), jres.end(), [](const JavaExe& a, const JavaExe& b){
        return a.version > b.version;
    });

    if(config.gameVersion == "1.7" || config.gameVersion == "1.8" || config.gameVersion == "1.12"){
        for(const auto& jre : jres){
            if(jre.version.majorVersion() == 16) return jre.exe;
        }
    }

    return jres.first().exe;
}