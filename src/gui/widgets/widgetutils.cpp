//
// Created by nils on 12/3/21.
//

#include "widgetutils.h"

QVBoxLayout *WidgetUtils::createOptional(QCheckBox *checkBox, QWidget *item) {
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(6);

    QObject::connect(checkBox, &QCheckBox::toggled, item, &QWidget::setEnabled);
    item->setDisabled(true);

    layout->addWidget(checkBox, 0, Qt::AlignHCenter);
    layout->addWidget(item);

    return layout;
}