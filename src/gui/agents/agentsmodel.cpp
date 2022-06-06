//
// Created by nils on 2/6/22.
//

#include <QFileInfo>

#include "agentsmodel.h"

AgentsModel::AgentsModel(QList<Agent> &agents, QObject *parent) : agents(agents), QAbstractTableModel(parent) {

}

int AgentsModel::rowCount(const QModelIndex &parent) const {
    return agents.size();
}

int AgentsModel::columnCount(const QModelIndex &parent) const {
    return Column::NUM_COLS;
}

QVariant AgentsModel::data(const QModelIndex &index, int role) const {
    Agent agent = agents[index.row()];

    if (index.column() == Column::OPTION) {
        switch (role) {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return agent.option;
        }
    } else if (index.column() == Column::NAME) {
        switch (role) {
            case Qt::DisplayRole:
                return agent.name;
            case Qt::ToolTipRole:
                return agent.path;
            case Qt::CheckStateRole:
                return agent.enabled;
        }
    }
    return {};
}

bool AgentsModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    Agent& agent = agents[index.row()];

    if (index.column() == Column::OPTION) {
        if (role == Qt::EditRole) {
            agent.option = value.toString();
            return true;
        }
    }else if(index.column() == Column::NAME){
        if(role == Qt::CheckStateRole){
            agent.enabled = !agent.enabled;
            return true;
        }
    }
    return false;
}

QVariant AgentsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case Column::NAME:
                return QString("Name");
            case Column::OPTION:
                return QString("Option");
        }
    }
    return {};
}

Qt::ItemFlags AgentsModel::flags(const QModelIndex &index) const {
    auto flags = QAbstractTableModel::flags(index);

    if(index.column() == Column::OPTION){
        flags |= Qt::ItemIsEditable;
    }else if(index.column() == Column::NAME){
        flags |= Qt::ItemIsUserCheckable;
    }

    return flags;
}

bool AgentsModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int i = 0; i < count; i++) {
        agents.removeAt(row);
    }

    endRemoveRows();
    return true;
}


// Stole this from QStringListModel
bool AgentsModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent,
                      int destinationChild) {
    beginMoveRows(QModelIndex(), sourceRow, sourceRow + count - 1, QModelIndex(), destinationChild);

    /*
    QList::move assumes that the second argument is the index where the item will end up to
    i.e. the valid range for that argument is from 0 to QList::size()-1
    QAbstractItemModel::moveRows when source and destinations have the same parent assumes that
    the item will end up being in the row BEFORE the one indicated by destinationChild
    i.e. the valid range for that argument is from 1 to QList::size()
    For this reason we remove 1 from destinationChild when using it inside QList
    */
    destinationChild--;
    const int fromRow = destinationChild < sourceRow ? (sourceRow + count - 1) : sourceRow;
    while (count--)
        agents.move(fromRow, destinationChild);

    endMoveRows();
    return true;
}

void AgentsModel::addAgent(const QString &path, const QString &option) {
    beginInsertRows(QModelIndex(), agents.size(), agents.size());
    agents.append({path, option});
    endInsertRows();
}
