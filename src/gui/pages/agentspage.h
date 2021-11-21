//
// Created by nils on 11/20/21.
//

#ifndef LUNAR_CLIENT_QT_AGENTSPAGE_H
#define LUNAR_CLIENT_QT_AGENTSPAGE_H

#include <QListWidget>

#include "configurationpage.h"

class AgentsPage : public ConfigurationPage {
Q_OBJECT
public:
    explicit AgentsPage(QWidget* parent = nullptr);

    QString title() override;
    QIcon icon() override;

    void save(QJsonObject& jsonObject) override;
    void load(const QJsonObject& jsonObject) override;

    QStringList getAgents();
private:
    void addAgent(const QString& path, bool select = false);
private:
    QListWidget* agents;
};


#endif //LUNAR_CLIENT_QT_AGENTSPAGE_H
