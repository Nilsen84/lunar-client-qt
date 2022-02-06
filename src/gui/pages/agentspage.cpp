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

class RemoveOutlineStyle : public QProxyStyle {
public:
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                       const QWidget *widget) const override {
        if(element != PE_FrameFocusRect){
            QProxyStyle::drawPrimitive(element, option, painter, widget);
        }
    }
};

AgentsPage::AgentsPage(Config& config, QWidget *parent) : ConfigurationPage(config, parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(20);

    agents = new QTableView(this);
    agents->setSelectionBehavior(QTableView::SelectRows);
    agents->setSelectionMode(QTableView::SingleSelection);
    agents->horizontalHeader()->setHighlightSections(false);
    agents->setAlternatingRowColors(true);
    agents->verticalHeader()->hide();
    auto style = new RemoveOutlineStyle;
    style->setParent(agents);
    agents->setStyle(style);
    agents->setModel((model = new AgentsModel(config.agents, this)));
    agents->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    agents->setAlternatingRowColors(true);


    add = new QPushButton(QStringLiteral("Add"));
    remove = new QPushButton(QStringLiteral("Remove"));
    moveUp = new QPushButton(QStringLiteral("Move Up"));
    moveDown = new QPushButton(QStringLiteral("Move Down"));

    connect(agents->selectionModel(), &QItemSelectionModel::selectionChanged, this, &AgentsPage::onSelect);

    remove->setDisabled(true);
    moveUp->setDisabled(true);
    moveDown->setDisabled(true);


    connect(add, &QPushButton::clicked, [this](){
        QStringList files = QFileDialog::getOpenFileNames(
                nullptr,
                QStringLiteral("Open Agent Jar"),
                {},
                QStringLiteral("Java Agent (*.jar)")
                );
        //bool added = false;
        foreach(const QString& str, files){
/*            if(!str.isEmpty()){
                foreach(const Agent& agent, this->config.agents){
                    if(agent.path == str){
                        goto skip;
                    }
                }*/

                model->addAgent(str, {});

/*                added = true;
            }

            skip:;*/

        }
   //     if(added)
        agents->selectRow(model->rowCount(QModelIndex())-1);
    });

    connect(remove, &QPushButton::clicked, [this](){
        foreach(const QModelIndex& item, agents->selectionModel()->selectedRows()){
            model->removeRow(item.row());
        }
    });

    connect(moveUp, &QPushButton::clicked, [this](){
        QModelIndexList selected = agents->selectionModel()->selectedRows();
        if(!selected.isEmpty()){
            int currentRow = selected[0].row();
            if(currentRow > 0){
                model->moveRow(QModelIndex(), currentRow-1, QModelIndex(), currentRow+1);
            }
        }
    });

    connect(moveDown, &QPushButton::clicked, [this](){
        QModelIndexList selected = agents->selectionModel()->selectedRows();
        if(!selected.isEmpty()) {
            int currentRow = selected[0].row();
            if (currentRow < model->rowCount(QModelIndex()) - 1) {
                model->moveRow(QModelIndex(), currentRow, QModelIndex(), currentRow+2);
            }
        }
    });

    QGridLayout* agentsContainer = new QGridLayout();
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

void AgentsPage::resizeEvent(QResizeEvent *event) {
    agents->setColumnWidth(Column::OPTION, agents->width() / 3);
    QWidget::resizeEvent(event);
}

void AgentsPage::onSelect(const QItemSelection &selected, const QItemSelection &deselected) {
    QModelIndexList selectedRows = qobject_cast<QItemSelectionModel*>(sender())->selectedRows();

    if(selectedRows.isEmpty()){
        remove->setDisabled(true);
        moveUp->setDisabled(true);
        moveDown->setDisabled(true);
    } else {
        remove->setEnabled(true);
        moveUp->setEnabled(true);
        moveDown->setEnabled(true);
    }
}
