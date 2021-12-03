//
// Created by nils on 12/2/21.
//

#include "filechooser.h"
#include <QHBoxLayout>
#include <QFileDialog>

FileChooser::FileChooser(QFileDialog::FileMode mode, QWidget *parent) : QWidget(parent){
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    pathEdit = new QLineEdit();
    QPushButton* button = new QPushButton();
    button->setIcon(QIcon(":/res/icons/openfolder.svg"));

    connect(pathEdit, &QLineEdit::returnPressed, [this](){pathEdit->clearFocus();});

    connect(button, &QPushButton::clicked, [mode, this](){
        QFileDialog fileDialog;
        fileDialog.setFileMode(mode);
        if(mode == QFileDialog::Directory)
            fileDialog.setOption(QFileDialog::ShowDirsOnly);
        if(fileDialog.exec()==QDialog::Accepted){
            QStringList files = fileDialog.selectedFiles();
            if(files.length() > 0){
                pathEdit->setText(files[0]);
            }
        }
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


