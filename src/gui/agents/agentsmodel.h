//
// Created by nils on 2/6/22.
//

#ifndef LUNAR_CLIENT_QT_AGENTSMODEL_H
#define LUNAR_CLIENT_QT_AGENTSMODEL_H

#include <QAbstractTableModel>

#include "config/config.h"

enum Column {
    NAME = 0,
    OPTION,
    NUM_COLS
};

class AgentsModel : public QAbstractTableModel {
Q_OBJECT
public:
    explicit AgentsModel(QList<Agent> &agents, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool removeRows(int row, int count, const QModelIndex &parent) override;

    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent,
                  int destinationChild) override;

    Qt::DropActions supportedDropActions() const override;

    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                         const QModelIndex &parent) const override;

    bool
    dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    void addAgent(const QString& path, const QString& option);

    bool containsPath(const QString& path) const;
private:
    QList<Agent> &agents;
};


#endif //LUNAR_CLIENT_QT_AGENTSMODEL_H
