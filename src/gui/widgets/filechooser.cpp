//
// Created by nils on 12/2/21.
//

#include "filechooser.h"
#include <QHBoxLayout>
#include <QFileDialog>

FileChooser::FileChooser(QWidget *parent) : QWidget(parent){
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);

    pathEdit = new QLineEdit();
    QPushButton* button = new QPushButton();
    button->setIcon(QIcon(":/res/icons/openfolder.svg"));

    connect(pathEdit, &QLineEdit::returnPressed, [this](){pathEdit->clearFocus();});

    connect(button, &QPushButton::clicked, [this](){
        QString fileName = QFileDialog::getOpenFileName();
        if(!fileName.isNull())
            pathEdit->setText(fileName);
    });

    layout->addWidget(pathEdit);
    layout->addWidget(button);
}

QString FileChooser::getPath() {
    return pathEdit->text();
}

void FileChooser::setPath(const QString &path) {
    pathEdit->setText(path);
}


