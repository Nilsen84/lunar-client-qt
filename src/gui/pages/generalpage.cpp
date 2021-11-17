//
// Created by nils on 11/5/21.
//

#include "generalpage.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>

GeneralPage::GeneralPage(QWidget *parent) : ConfigurationPage(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout();

    QCheckBox* keepMinMaxSame = new QCheckBox("Keep initial and maximum memory allocations the same");

    initialMemory = new QSlider(Qt::Horizontal);
    initialMemory->setMinimum(1024);
    initialMemory->setMaximum(16384);
    initialMemory->setPageStep(1024);

    maxMemory = new QSlider(Qt::Horizontal);
    maxMemory->setMinimum(1024);
    maxMemory->setMaximum(16384);
    maxMemory->setPageStep(1024);

    connect(keepMinMaxSame, &QCheckBox::toggled, this, &GeneralPage::keepMinMaxSameChanged);
    keepMinMaxSame->setChecked(true);

    mainLayout->addWidget(keepMinMaxSame);
    mainLayout->setAlignment(keepMinMaxSame, Qt::AlignHCenter);
    mainLayout->addWidget(initialMemory);
    mainLayout->addWidget(maxMemory);

    mainLayout->addSpacing(800);

    setLayout(mainLayout);
}

QString GeneralPage::title() {
    return "General";
}

void GeneralPage::keepMinMaxSameChanged(bool checked) {
    if(checked){
        maxMemory->setValue(initialMemory->value());
        connect(initialMemory, &QSlider::valueChanged, maxMemory, &QSlider::setValue, Qt::UniqueConnection);
        connect(maxMemory, &QSlider::valueChanged, initialMemory, &QSlider::setValue, Qt::UniqueConnection);
    }else{
        disconnect(initialMemory, &QSlider::valueChanged, maxMemory, &QSlider::setValue);
        disconnect(maxMemory, &QSlider::valueChanged, initialMemory, &QSlider::setValue);
    }
}
