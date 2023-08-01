//
// Created by nils on 6/6/22.
//

#include "agentsview.h"

#include <QHeaderView>
#include <QMouseEvent>

#include "gui/style/removeoutline.h"

AgentsView::AgentsView(QWidget *parent) : QTableView(parent) {
    setSelectionBehavior(QTableView::SelectRows);
    setSelectionMode(QTableView::SingleSelection);
    horizontalHeader()->setHighlightSections(false);
    setAlternatingRowColors(true);
    verticalHeader()->hide();
    auto style = new RemoveOutline;
    style->setParent(this);
    setStyle(style);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setAlternatingRowColors(true);

    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::DropOnly);
}

void AgentsView::keyPressEvent(QKeyEvent *event) {
    QAbstractItemView::keyPressEvent(event);

    if(!event->isAccepted() && event->key() == Qt::Key_Delete){
        for(const QModelIndex& idx : selectionModel()->selectedRows()){
            model()->removeRow(idx.row());
        }
    }
}
