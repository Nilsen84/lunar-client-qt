//
// Created by nils on 6/6/22.
//

#ifndef LUNAR_CLIENT_QT_AGENTSVIEW_H
#define LUNAR_CLIENT_QT_AGENTSVIEW_H

#include <QTableView>

class AgentsView : public QTableView {
public:
    explicit AgentsView(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};


#endif //LUNAR_CLIENT_QT_AGENTSVIEW_H
