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

AgentsPage::AgentsPage(QWidget *parent) : ConfigurationPage(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(20);

    agents = new QListWidget();
    QFont font;
    font.setPointSize(11);
    agents->setFont(font);
    agents->setAlternatingRowColors(true);


    QPalette palette;
    palette.setColor(QPalette::Disabled, QPalette::Text, Qt::blue);
    agents->setPalette(palette);

    QPushButton* add = new QPushButton(QStringLiteral("Add"));
    QPushButton* remove = new QPushButton(QStringLiteral("Remove"));
    QPushButton* moveUp = new QPushButton(QStringLiteral("Move Up"));
    QPushButton* moveDown = new QPushButton(QStringLiteral("Move Down"));

    connect(add, &QPushButton::clicked, [this](){
        QStringList files = QFileDialog::getOpenFileNames(
                nullptr,
                QStringLiteral("Open Agent Jar"),
                {},
                QStringLiteral("Java Agent (*.jar)")
                );
        for(const QString &str : files){
            if(!str.isEmpty()){
                addAgent(str, true);
            }
        }

    });

    connect(remove, &QPushButton::clicked, [this](){
        for(auto item : agents->selectedItems()){
            delete item;
        }
    });

    connect(moveUp, &QPushButton::clicked, [this](){
        int currentRow = agents->currentRow();
        if(currentRow > 0){
            auto currentItem = agents->takeItem(currentRow);
            agents->insertItem(currentRow - 1, currentItem);
            agents->setCurrentRow(currentRow - 1);
        }
    });

    connect(moveDown, &QPushButton::clicked, [this](){
        int currentRow = agents->currentRow();
        if(currentRow < agents->count()-1){
            auto currentItem = agents->takeItem(currentRow);
            agents->insertItem(currentRow + 1, currentItem);
            agents->setCurrentRow(currentRow + 1);
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

void AgentsPage::save(QJsonObject &jsonObject) {
    QJsonArray arr;
    for(const QString& str : getAgents())
        arr.append(str);

    jsonObject["agents"] = arr;
}

void AgentsPage::load(const QJsonObject &jsonObject) {
    QJsonArray arr = jsonObject["agents"].toArray();

    for(auto val : arr){
        QString path = val.toString();
        if(QFile::exists(path))
            addAgent(path);
    }
}

void AgentsPage::addAgent(const QString& path, bool select) {
    auto item = new QListWidgetItem(QFileInfo(path).fileName(), agents);
    item->setToolTip(path);
    if(select)
        agents->setCurrentItem(item);
}

QStringList AgentsPage::getAgents() {
    QStringList list;
    for(int i = 0; i < agents->count(); ++i){
        list << agents->item(i)->toolTip();
    }
    return list;
}
