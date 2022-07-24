//
// Created by nils on 6/6/22.
//

#include "removeoutline.h"

void RemoveOutline::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                                  const QWidget *widget) const {
    if(element != PE_FrameFocusRect){
        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
}
