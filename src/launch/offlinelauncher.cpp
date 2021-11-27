//
// Created by nils on 11/4/21.
//

#include "offlinelauncher.h"

#include <QProcess>
#include <QDir>
#include <QDirIterator>

const QString OfflineLauncher::lunarDir = QDir::homePath() + "/.lunarclient";
const QString OfflineLauncher::minecraftDir = QDir::homePath() + "/.minecraft";

OfflineLauncher::OfflineLauncher(QObject *parent) : Launcher(parent) {
}


void OfflineLauncher::launch(const LaunchData& launchData) {
    QProcess process;
    process.setProgram(launchData.findLunarJre ? findJavaExecutable() : launchData.customJre);

    process.setStandardInputFile(QProcess::nullDevice());
    process.setStandardOutputFile(QProcess::nullDevice());
    process.setStandardErrorFile(QProcess::nullDevice());

    QStringList args{
         "--add-modules", "jdk.naming.dns",
         "--add-exports", "jdk.naming.dns/com.sun.jndi.dns=java.naming",
         "-Djna.boot.library.path=natives",
         "--add-opens", "java.base/java.io=ALL-UNNAMED",
         QString("-Xms%1m").arg(launchData.initialMem),
         QString("-Xmx%1m").arg(launchData.maxMem),
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

    for(const QString& str : launchData.agents){
        args << "-javaagent:" + str;
    }

    args << QProcess::splitCommand(launchData.jvmArgs);
    args << "com.moonsworth.lunar.patcher.LunarMain";

    args << QStringList{
            "com.moonsworth.lunar.patcher.LunarMain",
            "--version", launchData.version,
            "--accessToken", "0",
            "--assetIndex", launchData.version == QStringLiteral("1.7") ? "1.7.10" : launchData.version,
            "--userProperties", "{}",
            "--gameDir", minecraftDir,
            "--texturesDir", lunarDir + "/textures",
            "--launcherVersion", "2.8.8",
            "--width", QString::number(launchData.windowWidth),
            "--height", QString::number(launchData.windowHeight)
    };

    process.setArguments(args);
    process.setWorkingDirectory(lunarDir+"/offline/"+launchData.version);

    process.startDetached();
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
