//
// Created by nils on 11/5/21.
//

#ifndef LUNAR_CLIENT_QT_CONFIGURATIONPAGE_H
#define LUNAR_CLIENT_QT_CONFIGURATIONPAGE_H

#include <QWidget>
#include <QString>
#include <QIcon>
#include "config/config.h"


class ConfigurationPage : public QWidget{
Q_OBJECT
public:
    virtual QString title() = 0;

    virtual QIcon icon() = 0;

    virtual void apply() = 0;
    virtual void load() = 0;

protected:
    explicit ConfigurationPage(Config& config, QWidget* parent);

    Config& config;
};


#endif //LUNAR_CLIENT_QT_CONFIGURATIONPAGE_H
