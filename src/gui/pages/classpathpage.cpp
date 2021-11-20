//
// Created by nils on 11/20/21.
//

#include "classpathpage.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

ClasspathPage::ClasspathPage(QWidget *parent) : ConfigurationPage(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(20);

    {
        classpath = new QListWidget();
        QPushButton* add = new QPushButton("Add");
        QPushButton* remove = new QPushButton("Remove");
        QPushButton* moveUp = new QPushButton("Move Up");
        QPushButton* moveDown = new QPushButton("Move Down");

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
