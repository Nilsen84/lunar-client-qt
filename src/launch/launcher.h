//
// Created by nils on 11/4/21.
//

#ifndef LUNAR_CLIENT_QT_LAUNCHER_H
#define LUNAR_CLIENT_QT_LAUNCHER_H

#include <QObject>

class Launcher : public QObject{
Q_OBJECT
public:
    explicit Launcher(QObject* parent = nullptr);

    void launch(bool offline);
signals:
    void finished();
};


#endif //LUNAR_CLIENT_QT_LAUNCHER_H
