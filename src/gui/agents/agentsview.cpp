//
// Created by nils on 6/6/22.
//

#include "agentsview.hpp"

#include <QHeaderView>
#include <QMouseEvent>

#include "gui/style/removeoutline.hpp"

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