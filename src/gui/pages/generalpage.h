//
// Created by nils on 11/5/21.
//

#ifndef LUNAR_CLIENT_QT_GENERALPAGE_H
#define LUNAR_CLIENT_QT_GENERALPAGE_H

#include <QSlider>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPlainTextEdit>

#include "configurationpage.h"

class GeneralPage : public ConfigurationPage{
Q_OBJECT
public:
    explicit GeneralPage(Config& config, QWidget* parent = nullptr);

    QString title() override;

    QIcon icon() override;

    void apply() override;
    void load() override;

private slots:
    void keepMinMaxSameChanged(bool checked);
private:
    QCheckBox* keepMemorySame;
    QSlider* initialMemory;
    QSlider* maxMemory;

    QSpinBox* windowWidth;
    QSpinBox* windowHeight;

    QCheckBox* useCustomJre;
    QLineEdit* jreLine;

    QPlainTextEdit* jvmArgs;
};


#endif //LUNAR_CLIENT_QT_GENERALPAGE_H
