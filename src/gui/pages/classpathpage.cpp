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
        classpath = new QListWidget();
        QFont font;
        font.setPointSize(14);
        classpath->setFont(font);
        auto lunarClasses = new QListWidgetItem("<Lunar Classes>", classpath);
        lunarClasses->setFlags(Qt::NoItemFlags);

        QPalette palette;
        palette.setColor(QPalette::Disabled, QPalette::Text, Qt::blue);
        classpath->setPalette(palette);

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
                    auto item = new QListWidgetItem(QFileInfo(str).fileName(), classpath);
                    item->setToolTip(str);
                    classpath->setCurrentItem(item);
                }
            }

        });

        connect(remove, &QPushButton::clicked, [this](){
            for(auto item : classpath->selectedItems()){
                delete item;
            }
        });

        connect(moveUp, &QPushButton::clicked, [this](){
            int currentRow = classpath->currentRow();
            if(currentRow > 0){
                auto currentItem = classpath->takeItem(currentRow);
                classpath->insertItem(currentRow - 1, currentItem);
                classpath->setCurrentRow(currentRow - 1);
            }
        });

        connect(moveDown, &QPushButton::clicked, [this](){
            int currentRow = classpath->currentRow();
            if(currentRow < classpath->count()-1){
                auto currentItem = classpath->takeItem(currentRow);
                classpath->insertItem(currentRow + 1, currentItem);
                classpath->setCurrentRow(currentRow + 1);
            }
        });

        QGridLayout* classPathContainer = new QGridLayout();
        classPathContainer->setSpacing(6);
        QLabel* label = new QLabel("Classpath");
        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        classPathContainer->addWidget(label, 0, 0, Qt::AlignHCenter);
        classPathContainer->addWidget(classpath, 1, 0, 5, 1);
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
