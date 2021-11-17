//
// Created by nils on 11/5/21.
//

#ifndef LUNAR_CLIENT_QT_GENERALPAGE_H
#define LUNAR_CLIENT_QT_GENERALPAGE_H

#include <QSlider>
#include <QCheckBox>

#include "configurationpage.h"

class GeneralPage : public ConfigurationPage{
public:
    explicit GeneralPage(QWidget* parent = nullptr);

    QString title() override;
private slots:
    void keepMinMaxSameChanged(bool checked);
private:
    QSlider* initialMemory;
    QSlider* maxMemory;
};


#endif //LUNAR_CLIENT_QT_GENERALPAGE_H
