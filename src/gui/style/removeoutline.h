//
// Created by nils on 6/6/22.
//

#ifndef LUNAR_CLIENT_QT_REMOVEOUTLINE_H
#define LUNAR_CLIENT_QT_REMOVEOUTLINE_H


#include <QProxyStyle>

class RemoveOutline : public QProxyStyle {
public:
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                       const QWidget *widget) const override;
};

#endif //LUNAR_CLIENT_QT_REMOVEOUTLINE_H
