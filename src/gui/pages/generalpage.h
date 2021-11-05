//
// Created by nils on 11/5/21.
//

#ifndef LUNAR_CLIENT_QT_GENERALPAGE_H
#define LUNAR_CLIENT_QT_GENERALPAGE_H

#include <QPushButton>

#include "configurationpage.h"

class GeneralPage : public ConfigurationPage{
public:
    explicit GeneralPage(QWidget* parent = nullptr);

    QString title() override;
private:
    QPushButton* btn;
};


#endif //LUNAR_CLIENT_QT_GENERALPAGE_H
