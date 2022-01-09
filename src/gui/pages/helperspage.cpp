//
// Created by nils on 11/20/21.
//

#include "helperspage.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>

HelpersPage::HelpersPage(Config& config, QWidget *parent) : ConfigurationPage(config, parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(20);

    helpers = new QListWidget();
    QFont font;
    font.setPointSize(11);
    helpers->setFont(font);
    helpers->setAlternatingRowColors(true);

    QPalette palette;
    palette.setColor(QPalette::Disabled, QPalette::Text, Qt::blue);
    helpers->setPalette(palette);

    QPushButton* add = new QPushButton(QStringLiteral("Add"));
    QPushButton* remove = new QPushButton(QStringLiteral("Remove"));
    QPushButton* moveUp = new QPushButton(QStringLiteral("Move Up"));
    QPushButton* moveDown = new QPushButton(QStringLiteral("Move Down"));

    connect(add, &QPushButton::clicked, [this](){
        QStringList files = QFileDialog::getOpenFileNames(
                nullptr,
                QStringLiteral("Open Helper Executable"),
                {},
                QStringLiteral("Helper Executable (*.exe)")
                );
        foreach(const QString& str, files){
            if(!str.isEmpty()){
                addHelper(str, true);
            }
        }
    });

    connect(remove, &QPushButton::clicked, [this](){
        foreach(QListWidgetItem* item, helpers->selectedItems()){
            delete item;
        }
    });

    connect(moveUp, &QPushButton::clicked, [this](){
        int currentRow = helpers->currentRow();
        if(currentRow > 0){
            auto currentItem = helpers->takeItem(currentRow);
            helpers->insertItem(currentRow - 1, currentItem);
            helpers->setCurrentRow(currentRow - 1);
        }
    });

    connect(moveDown, &QPushButton::clicked, [this](){
        int currentRow = helpers->currentRow();
        if(currentRow < helpers->count()-1){
            auto currentItem = helpers->takeItem(currentRow);
            helpers->insertItem(currentRow + 1, currentItem);
            helpers->setCurrentRow(currentRow + 1);
        }
    });

    QGridLayout* helpersContainer = new QGridLayout();
    helpersContainer->setSpacing(6);
    helpersContainer->addWidget(helpers, 0, 0, 5, 1);
    helpersContainer->addWidget(add, 0, 1);
    helpersContainer->addWidget(remove, 1, 1);
    helpersContainer->addWidget(moveUp, 2, 1);
    helpersContainer->addWidget(moveDown, 3, 1);

    mainLayout->addLayout(helpersContainer);


    setLayout(mainLayout);
}


QString HelpersPage::title() {
    return QStringLiteral("Helpers");
}

QIcon HelpersPage::icon() {
    return QIcon(":/res/icons/helper.svg");
}

void HelpersPage::apply() {
    config.helpers = getHelpers();
}

void HelpersPage::load() {
    foreach(const QString &path, config.helpers) {
        if (QFile::exists(path)) {
            addHelper(path);
        }
    }
}

void HelpersPage::addHelper(const QString& path, bool select) {
    auto item = new QListWidgetItem(QFileInfo(path).fileName(), helpers);
    item->setToolTip(path);
    if(select)
        helpers->setCurrentItem(item);
}

QStringList HelpersPage::getHelpers() {
    QStringList list;
    for(int i = 0; i < helpers->count(); ++i){
        list << helpers->item(i)->toolTip();
    }
    return list;
}
