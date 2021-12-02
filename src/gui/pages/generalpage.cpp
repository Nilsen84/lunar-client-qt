//
// Created by nils on 11/5/21.
//

#include "generalpage.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QFileDialog>

GeneralPage::GeneralPage(Config& config, QWidget *parent) : ConfigurationPage(config, parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(40);

    keepMemorySame = new QCheckBox(QStringLiteral("Keep initial and maximum memory allocations the same"));

    QLabel* initialMemoryLabel = new QLabel();
    initialMemory = new QSlider(Qt::Horizontal);
    initialMemory->setMinimum(1024);
    initialMemory->setMaximum(16384);
    initialMemory->setPageStep(1024);

    QLabel* maxMemoryLabel = new QLabel();
    maxMemory = new QSlider(Qt::Horizontal);
    maxMemory->setMinimum(1024);
    maxMemory->setMaximum(16384);
    maxMemory->setPageStep(1024);

    //Memory slider functionality
    connect(initialMemory, &QSlider::valueChanged, [initialMemoryLabel](int val){initialMemoryLabel->setText("Initial Memory:  " + QString::number(val) + " MiB");});
    connect(maxMemory, &QSlider::valueChanged, [maxMemoryLabel](int val){maxMemoryLabel->setText("Maximum Memory:  " + QString::number(val) + " MiB");});

    connect(keepMemorySame, &QCheckBox::toggled, this, &GeneralPage::keepMinMaxSameChanged);

    //Memory slider group
    QVBoxLayout* memorySliderContainer = new QVBoxLayout();
    memorySliderContainer->setSpacing(6);

    memorySliderContainer->addWidget(initialMemoryLabel, 0, Qt::AlignHCenter);
    memorySliderContainer->addWidget(initialMemory);
    memorySliderContainer->addSpacing(30);
    memorySliderContainer->addWidget(maxMemoryLabel, 0, Qt::AlignHCenter);
    memorySliderContainer->addWidget(maxMemory);

    //Window resolution
    windowWidth = new QSpinBox();
    windowHeight = new QSpinBox();

    windowWidth->setMinimum(0);
    windowWidth->setMaximum(99999);

    windowHeight->setMinimum(0);
    windowHeight->setMaximum(99999);

    //Window resolution group
    QHBoxLayout* windowResContainer = new QHBoxLayout();
    windowResContainer->setSpacing(30);
    windowResContainer->addWidget(new QLabel(QStringLiteral("Window width")));
    windowResContainer->addWidget(windowWidth, 1);
    windowResContainer->addWidget(new QLabel(QStringLiteral("Window height")));
    windowResContainer->addWidget(windowHeight, 1);

    //Custom jre checkbox lineedit and button
    useCustomJre = new QCheckBox(QStringLiteral("Use custom jre"));

    jreLine = new QLineEdit();
    QPushButton* openFile = new QPushButton();
    openFile->setIcon(QIcon(":/res/icons/openfolder.svg"));

    jreLine->setDisabled(true);
    openFile->setDisabled(true);

    connect(useCustomJre, &QCheckBox::toggled, jreLine, &QLineEdit::setEnabled);
    connect(useCustomJre, &QCheckBox::toggled, openFile, &QPushButton::setEnabled);
    connect(jreLine, &QLineEdit::returnPressed, [this](){jreLine->clearFocus();});

    connect(openFile, &QPushButton::clicked, [this](){
        QString fileName = QFileDialog::getOpenFileName();
        if(!fileName.isNull())
            jreLine->setText(fileName);
    });

    //Custom jre groups
    QGridLayout* customJreContainer = new QGridLayout();
    customJreContainer->setSpacing(6);
    customJreContainer->addWidget(useCustomJre, 0, 0, 1, -1, Qt::AlignHCenter);
    customJreContainer->addWidget(jreLine, 1, 0);
    customJreContainer->addWidget(openFile, 1, 1);

    //Jvm arguments
    QVBoxLayout* jvmArgsGroup = new QVBoxLayout();
    jvmArgsGroup->setSpacing(6);

    jvmArgs = new QPlainTextEdit();

    jvmArgsGroup->addWidget(new QLabel(QStringLiteral("JVM Arguments")), 0, Qt::AlignHCenter);
    jvmArgsGroup->addWidget(jvmArgs);


    mainLayout->addWidget(keepMemorySame, 0, Qt::AlignHCenter);
    mainLayout->addLayout(memorySliderContainer);
    mainLayout->addLayout(windowResContainer);
    mainLayout->addLayout(customJreContainer);
    mainLayout->addLayout(jvmArgsGroup, 1);

    setLayout(mainLayout);
}

QString GeneralPage::title() {
    return QStringLiteral("General");
}

QIcon GeneralPage::icon() {
    return QIcon(":/res/icons/cog.svg");
}

void GeneralPage::apply() {
    config.keepMemorySame = keepMemorySame->isChecked();
    config.initialMemory = initialMemory->value();
    config.maximumMemory = maxMemory->value();

    config.windowWidth = windowWidth->value();
    config.windowHeight = windowHeight->value();

    config.useCustomJre = useCustomJre->isChecked();
    config.customJrePath = jreLine->text();

    config.jvmArgs = jvmArgs->toPlainText();
}

void GeneralPage::load() {
    keepMemorySame->setChecked(config.keepMemorySame);

    initialMemory->setValue(config.initialMemory);
    maxMemory->setValue(config.maximumMemory);

    windowWidth->setValue(config.windowWidth);
    windowHeight->setValue(config.windowHeight);

    useCustomJre->setChecked(config.useCustomJre);
    jreLine->setText(config.customJrePath);

    jvmArgs->setPlainText(config.jvmArgs);
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