//
// Created by nils on 11/20/21.
//

#ifndef LUNAR_CLIENT_QT_AGENTSPAGE_H
#define LUNAR_CLIENT_QT_AGENTSPAGE_H

#include <QListWidget>
#include <QTableView>
#include <QPushButton>

#include "configurationpage.h"
#include "../agents/agentsmodel.h"

class AgentsPage : public ConfigurationPage {
Q_OBJECT
public:
    explicit AgentsPage(Config& config, QWidget* parent = nullptr);

    QString title() override;

    QString description() override;

    QIcon icon() override;

    void apply() override;
    void load() override;
private slots:
    void onSelect(const QItemSelection & selected, const QItemSelection & deselected);

private:
    AgentsModel* model;
    QTableView* agents;

    QPushButton* add;
    QPushButton* remove;
    QPushButton* moveUp;
    QPushButton* moveDown;
};


#endif //LUNAR_CLIENT_QT_AGENTSPAGE_H
