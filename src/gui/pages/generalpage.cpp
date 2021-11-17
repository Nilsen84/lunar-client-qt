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

    QLabel* initialMemoryLabel = new QLabel();
    QLabel* maxMemoryLabel = new QLabel();

    initialMemory = new QSlider(Qt::Horizontal);
    initialMemory->setMinimum(1024);
    initialMemory->setMaximum(16384);
    initialMemory->setPageStep(1024);

    maxMemory = new QSlider(Qt::Horizontal);
    maxMemory->setMinimum(1024);
    maxMemory->setMaximum(16384);
    maxMemory->setPageStep(1024);

    connect(initialMemory, &QSlider::valueChanged, [initialMemoryLabel](int val){initialMemoryLabel->setText("Initial Memory:  " + QString::number(val) + " MiB");});
    connect(maxMemory, &QSlider::valueChanged, [maxMemoryLabel](int val){maxMemoryLabel->setText("Maximum Memory:  " + QString::number(val) + " MiB");});

    initialMemory->setValue(16384/4);
    maxMemory->setValue(16384/4);

    connect(keepMinMaxSame, &QCheckBox::toggled, this, &GeneralPage::keepMinMaxSameChanged);
    keepMinMaxSame->setChecked(true);

    mainLayout->addWidget(keepMinMaxSame);
    mainLayout->setAlignment(keepMinMaxSame, Qt::AlignHCenter);

    mainLayout->addSpacing(40);

    mainLayout->addWidget(initialMemoryLabel);
    mainLayout->setAlignment(initialMemoryLabel, Qt::AlignHCenter);
    mainLayout->addWidget(initialMemory);

    mainLayout->addSpacing(30);


    mainLayout->addWidget(maxMemoryLabel);
    mainLayout->setAlignment(maxMemoryLabel, Qt::AlignHCenter);
    mainLayout->addWidget(maxMemory);

    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

QString GeneralPage::title() {
    return "General";
}

void GeneralPage::keepMinMaxSameChanged(bool checked) {
    if(checked){
        initialMemory->setValue(maxMemory->value());
        maxMemory->setDisabled(true);
        connect(initialMemory, &QSlider::valueChanged, maxMemory, &QSlider::setValue, Qt::UniqueConnection);
    }else{
        maxMemory->setEnabled(true);
        disconnect(initialMemory, &QSlider::valueChanged, maxMemory, &QSlider::setValue);
        //disconnect(maxMemory, &QSlider::valueChanged, initialMemory, &QSlider::setValue);
    }
}
