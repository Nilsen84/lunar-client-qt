//
// Created by nils on 11/20/21.
//

#ifndef LUNAR_CLIENT_QT_CLASSPATHPAGE_H
#define LUNAR_CLIENT_QT_CLASSPATHPAGE_H

#include "configurationpage.h"

class ClasspathPage : public ConfigurationPage {
Q_OBJECT
public:
    explicit ClasspathPage(QWidget* parent = nullptr);

    QString title() override;
    QIcon icon() override;

    void save(QJsonObject& jsonObject) override;
    void load(const QJsonObject& jsonObject) override;
};


#endif //LUNAR_CLIENT_QT_CLASSPATHPAGE_H
