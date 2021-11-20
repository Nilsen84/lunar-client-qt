//
// Created by nils on 11/20/21.
//

#include "classpathpage.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>


ClasspathPage::ClasspathPage(QWidget *parent) : ConfigurationPage(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(20);

    {
        agents = new QListWidget();
        QFont font;
        font.setPointSize(14);
        agents->setFont(font);
/*        auto lunarClasses = new QListWidgetItem("<Lunar Classes>", classpath);
        lunarClasses->setFlags(Qt::NoItemFlags);*/

        QPalette palette;
        palette.setColor(QPalette::Disabled, QPalette::Text, Qt::blue);
        agents->setPalette(palette);

        QPushButton* add = new QPushButton("Add");
        QPushButton* remove = new QPushButton("Remove");
        QPushButton* moveUp = new QPushButton("Move Up");
        QPushButton* moveDown = new QPushButton("Move Down");

        connect(add, &QPushButton::clicked, [this](){
            QStringList files = QFileDialog::getOpenFileNames(
                    nullptr,
                    "Open JAR",
                    {},
                    "JAR Archives (*.jar)"
                    );
            for(const QString &str : files){
                if(!str.isEmpty()){
                    auto item = new QListWidgetItem(QFileInfo(str).fileName(), agents);
                    item->setToolTip(str);
                    agents->setCurrentItem(item);
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

        QGridLayout* classPathContainer = new QGridLayout();
        classPathContainer->setSpacing(6);
        QLabel* label = new QLabel("Agents");
        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        classPathContainer->addWidget(label, 0, 0, Qt::AlignHCenter);
        classPathContainer->addWidget(agents, 1, 0, 5, 1);
        classPathContainer->addWidget(add, 1, 1);
        classPathContainer->addWidget(remove, 2, 1);
        classPathContainer->addWidget(moveUp, 3, 1);
        classPathContainer->addWidget(moveDown, 4, 1);

        mainLayout->addLayout(classPathContainer);
    }

    setLayout(mainLayout);
}


QString ClasspathPage::title() {
    return QStringLiteral("Classpath & Agents");
}

QIcon ClasspathPage::icon() {
    return QIcon(":/res/icons/agent.svg");
}

void ClasspathPage::save(QJsonObject &jsonObject) {

}

void ClasspathPage::load(const QJsonObject &jsonObject) {

}
