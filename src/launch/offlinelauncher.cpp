//
// Created by nils on 11/4/21.
//

#include "offlinelauncher.h"

#include <QProcess>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>

const QString OfflineLauncher::lunarDir = QDir::homePath() + "/.lunarclient";
const QString OfflineLauncher::minecraftDir =
#if defined(Q_OS_WIN)
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/.minecraft";
#elif defined(Q_OS_DARWIN)
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/minecraft";
#else
        QDir::homePath() + "/.minecraft";
#endif

OfflineLauncher::OfflineLauncher(QObject *parent) : Launcher(parent) {
}


void OfflineLauncher::launch(const LaunchOptions& launchOptions) {
    QProcess process;
    process.setProgram(launchOptions.findLunarJre ? findJavaExecutable() : launchOptions.customJre);

    process.setStandardInputFile(QProcess::nullDevice());
    process.setStandardOutputFile(QProcess::nullDevice());
    process.setStandardErrorFile(QProcess::nullDevice());

    QStringList args{
         "--add-modules", "jdk.naming.dns",
         "--add-exports", "jdk.naming.dns/com.sun.jndi.dns=java.naming",
         "-Djna.boot.library.path=natives",
         "--add-opens", "java.base/java.io=ALL-UNNAMED",
         QString("-Xms%1m").arg(launchOptions.initialMem),
         QString("-Xmx%1m").arg(launchOptions.maxMem),
         "-Djava.library.path=natives",
         "-cp", QStringList({
                    "vpatcher-prod.jar",
                    "lunar-prod-optifine.jar",
                    "lunar-libs.jar",
                    "lunar-assets-prod-1-optifine.jar",
                    "lunar-assets-prod-2-optifine.jar",
                    "lunar-assets-prod-3-optifine.jar",
                    "OptiFine.jar"
        }).join(QDir::listSeparator())
    };

    for(const QString& str : launchOptions.agents){
        args << "-javaagent:" + str;
    }

    args << QProcess::splitCommand(launchOptions.jvmArgs);
    args << "com.moonsworth.lunar.patcher.LunarMain";

    args << QStringList{
            "com.moonsworth.lunar.patcher.LunarMain",
            "--version", launchOptions.version,
            "--accessToken", "0",
            "--assetIndex", launchOptions.version == QStringLiteral("1.7") ? "1.7.10" : launchOptions.version,
            "--userProperties", "{}",
            "--gameDir", minecraftDir,
            "--texturesDir", lunarDir + "/textures",
            "--launcherVersion", "2.8.8",
            "--width", QString::number(launchOptions.windowWidth),
            "--height", QString::number(launchOptions.windowHeight)
    };

    process.setArguments(args);
    process.setWorkingDirectory(lunarDir + "/offline/" + launchOptions.version);

    if(!process.startDetached()){
        emit error("Failed to start process: " + process.errorString());
    }
}

QString OfflineLauncher::findJavaExecutable() {
    QDirIterator it(lunarDir+"/jre", QDir::Dirs | QDir::NoDotAndDotDot);

    while(it.hasNext()){
        QString potentialExecutable = it.next() +
#ifdef Q_OS_WIN
        "/bin/javaw.exe";
#else
        "/bin/java";
#endif

        if(QFileInfo(potentialExecutable).isExecutable())
            return potentialExecutable;
    }

    return {};
}
