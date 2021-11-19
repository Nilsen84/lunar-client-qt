//
// Created by nils on 11/5/21.
//

#include "generalpage.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QFileDialog>

GeneralPage::GeneralPage(QWidget *parent) : ConfigurationPage(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout();

    QCheckBox* keepMinMaxSame = new QCheckBox(QStringLiteral("Keep initial and maximum memory allocations the same"));

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

    mainLayout->addWidget(keepMinMaxSame, 0, Qt::AlignHCenter);

    mainLayout->addSpacing(40);

    mainLayout->addWidget(initialMemoryLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(initialMemory);

    mainLayout->addSpacing(30);


    mainLayout->addWidget(maxMemoryLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(maxMemory);

    mainLayout->addSpacing(40);

    QHBoxLayout* hLayout = new QHBoxLayout();
    QCheckBox* useCustomJre = new QCheckBox(QStringLiteral("Use custom jre"));
    jreLine = new QLineEdit();
    QPushButton* openFile = new QPushButton();
    openFile->setIcon(QIcon(":/res/icons/openfolder.svg"));

    hLayout->addWidget(jreLine);
    hLayout->addWidget(openFile);
    jreLine->setDisabled(true);
    openFile->setDisabled(true);


    connect(useCustomJre, &QCheckBox::toggled, jreLine, &QLineEdit::setEnabled);
    connect(useCustomJre, &QCheckBox::toggled, openFile, &QPushButton::setEnabled);
    connect(jreLine, &QLineEdit::returnPressed, [this](){jreLine->clearFocus();});

    connect(openFile, &QPushButton::clicked, [this](){
       jreLine->setText(QFileDialog ::getOpenFileName());
    });

    mainLayout->addWidget(useCustomJre, 0, Qt::AlignHCenter);
    mainLayout->addLayout(hLayout);


    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

QString GeneralPage::title() {
    return QStringLiteral("General");
}

QIcon GeneralPage::icon() {
    return QIcon(":/res/icons/cog.svg");
}

void GeneralPage::keepMinMaxSameChanged(bool checked) {
    if(checked){
        initialMemory->setValue(maxMemory->value());
        maxMemory->setDisabled(true);
        connect(initialMemory, &QSlider::valueChanged, maxMemory, &QSlider::setValue, Qt::UniqueConnection);
    }else{
        maxMemory->setEnabled(true);
        disconnect(initialMemory, &QSlider::valueChanged, maxMemory, &QSlider::setValue);
    }
}

int GeneralPage::getInitialMemory() {
    return initialMemory->value();
}

int GeneralPage::getMaxMemory() {
    return maxMemory->value();
}
