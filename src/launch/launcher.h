//
// Created by nils on 11/27/21.
//

#ifndef LUNAR_CLIENT_QT_LAUNCHER_H
#define LUNAR_CLIENT_QT_LAUNCHER_H

#include <QObject>
#include "config/config.h"

class Launcher : public QObject {
Q_OBJECT
public:
    enum class CosmeticsState {
        OFF,
        DEFAULT,
        UNLOCKED
    };

    Launcher(const Config& config, QObject* parent);

    virtual bool launch(CosmeticsState cosmeticsState) = 0;
protected:
    const Config& config;
};

#endif //LUNAR_CLIENT_QT_LAUNCHER_H
