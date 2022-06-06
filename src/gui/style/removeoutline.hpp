//
// Created by nils on 6/6/22.
//

#ifndef LUNAR_CLIENT_QT_REMOVEOUTLINE_HPP
#define LUNAR_CLIENT_QT_REMOVEOUTLINE_HPP


#include <QProxyStyle>

class RemoveOutline : public QProxyStyle {
public:
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                       const QWidget *widget) const override {
        if(element != PE_FrameFocusRect){
            QProxyStyle::drawPrimitive(element, option, painter, widget);
        }
    }
};

#endif //LUNAR_CLIENT_QT_REMOVEOUTLINE_HPP
