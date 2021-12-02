//
// Created by nils on 12/2/21.
//

#ifndef LUNAR_CLIENT_QT_MINECRAFTPAGE_H
#define LUNAR_CLIENT_QT_MINECRAFTPAGE_H

#include "configurationpage.h"

class MinecraftPage : public ConfigurationPage {
Q_OBJECT
public:
    explicit MinecraftPage(Config& config, QWidget* parent = nullptr);

    QString title() override;
    QIcon icon() override;

    void apply() override;
    void load() override;
private:

};


#endif //LUNAR_CLIENT_QT_MINECRAFTPAGE_H
