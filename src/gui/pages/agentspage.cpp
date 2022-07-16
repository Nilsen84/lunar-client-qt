//
// Created by nils on 11/20/21.
//

#include "agentspage.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QProxyStyle>
#include <QHeaderView>
#include <QItemSelectionModel>

AgentsPage::AgentsPage(Config &config, QWidget *parent) : ConfigurationPage(config, parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(20);

    agents = new AgentsView(this);
    agents->setModel((model = new AgentsModel(config.agents, this)));

    add = new QPushButton(QStringLiteral("Add"));
    remove = new QPushButton(QStringLiteral("Remove"));
    moveUp = new QPushButton(QStringLiteral("Move Up"));
    moveDown = new QPushButton(QStringLiteral("Move Down"));

    connect(agents->selectionModel(), &QItemSelectionModel::selectionChanged, this, &AgentsPage::onSelect);

    remove->setDisabled(true);
    moveUp->setDisabled(true);
    moveDown->setDisabled(true);

    connect(add, &QPushButton::clicked, [this]() {
        QStringList files = QFileDialog::getOpenFileNames(
                nullptr,
                QStringLiteral("Open Agent Jar"),
                {},
                QStringLiteral("Java Agent (*.jar)")
        );

        for(const QString& str : files){
            model->addAgent(str, {});
        }

        agents->selectRow(model->rowCount(QModelIndex()) - 1);
    });

    connect(remove, &QPushButton::clicked, [this]() {
        for(const QModelIndex &item : agents->selectionModel()->selectedRows()) {
            model->removeRow(item.row());
        }
    });

    connect(moveUp, &QPushButton::clicked, [this]() {
        QModelIndexList selected = agents->selectionModel()->selectedRows();
        if (!selected.isEmpty()) {
            int currentRow = selected[0].row();
            if (currentRow > 0) {
                model->moveRow(QModelIndex(), currentRow - 1, QModelIndex(), currentRow + 1);
            }
        }
    });

    connect(moveDown, &QPushButton::clicked, [this]() {
        QModelIndexList selected = agents->selectionModel()->selectedRows();
        if (!selected.isEmpty()) {
            int currentRow = selected[0].row();
            if (currentRow < model->rowCount(QModelIndex()) - 1) {
                model->moveRow(QModelIndex(), currentRow, QModelIndex(), currentRow + 2);
            }
        }
    });

    QGridLayout *agentsContainer = new QGridLayout();
    agentsContainer->setSpacing(6);
    agentsContainer->addWidget(agents, 0, 0, 5, 1);
    agentsContainer->addWidget(add, 0, 1);
    agentsContainer->addWidget(remove, 1, 1);
    agentsContainer->addWidget(moveUp, 2, 1);
    agentsContainer->addWidget(moveDown, 3, 1);

    mainLayout->addLayout(agentsContainer);


    setLayout(mainLayout);
}


QString AgentsPage::title() {
    return QStringLiteral("Agents");
}

QIcon AgentsPage::icon() {
    return QIcon(":/res/icons/agent.svg");
}

void AgentsPage::apply() {
}

void AgentsPage::load() {
}

void AgentsPage::onSelect(const QItemSelection &selected, const QItemSelection &deselected) {
    QModelIndexList selectedRows = qobject_cast<QItemSelectionModel *>(sender())->selectedRows();

    if (selectedRows.isEmpty()) {
        remove->setDisabled(true);
        moveUp->setDisabled(true);
        moveDown->setDisabled(true);
    } else {
        remove->setEnabled(true);
        moveUp->setEnabled(true);
        moveDown->setEnabled(true);
    }
}

QString AgentsPage::description() {
    return "List of agents you want to use. Don't add any Forge/Fabric mods or else your game won't start.";
}
