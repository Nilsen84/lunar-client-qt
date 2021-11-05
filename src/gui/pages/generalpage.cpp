//
// Created by nils on 11/5/21.
//

#include "generalpage.h"

#include "QVBoxLayout"

GeneralPage::GeneralPage(QWidget *parent) : ConfigurationPage(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout();

    btn = new QPushButton("TestButton", this);

    mainLayout->addWidget(btn);

    setLayout(mainLayout);
}

QString GeneralPage::title() {
    return "General";
}
