//
// Created by nils on 12/3/21.
//

#ifndef LUNAR_CLIENT_QT_WIDGETUTILS_H
#define LUNAR_CLIENT_QT_WIDGETUTILS_H

#include <QVBoxLayout>
#include <QCheckBox>

namespace WidgetUtils {
    QVBoxLayout* createOptional(QCheckBox* checkBox, QWidget* item);
}


#endif //LUNAR_CLIENT_QT_WIDGETUTILS_H
