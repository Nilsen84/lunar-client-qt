//
// Created by nils on 11/5/21.
//

#ifndef LUNAR_CLIENT_QT_CONFIGURATIONPAGE_H
#define LUNAR_CLIENT_QT_CONFIGURATIONPAGE_H

#include <QWidget>

class ConfigurationPage : public QWidget{
Q_OBJECT
public:
    virtual QString title() = 0;
protected:
    explicit ConfigurationPage(QWidget* parent);
};


#endif //LUNAR_CLIENT_QT_CONFIGURATIONPAGE_H
