//
// Created by nils on 11/20/21.
//

#ifndef LUNAR_CLIENT_QT_AGENTSPAGE_H
#define LUNAR_CLIENT_QT_AGENTSPAGE_H

#include <QListWidget>
#include <QTableView>

#include "configurationpage.h"
#include "../agents/agentsmodel.h"

class AgentsPage : public ConfigurationPage {
Q_OBJECT
public:
    explicit AgentsPage(Config& config, QWidget* parent = nullptr);

    QString title() override;
    QIcon icon() override;

    void apply() override;
    void load() override;
private:

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    AgentsModel* model;
    QTableView* agents;
};


#endif //LUNAR_CLIENT_QT_AGENTSPAGE_H
