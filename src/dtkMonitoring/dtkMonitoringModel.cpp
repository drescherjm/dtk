#include "dtkMonitoringModel.h"

dtkMonitoringModel::dtkMonitoringModel()
{

}

dtkMonitoringModel::~dtkMonitoringModel()
{

}

int dtkMonitoringModel::rowCount(const QModelIndex &parent) const
{
    return dtkMonitoringController::instance()->nodeCount();
}

QVariant dtkMonitoringModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

    if (index.row() >= dtkMonitoringController::instance()->nodeCount())
        return QVariant();

    if (role == Qt::DisplayRole)
        return dtkMonitoringController::instance()->nodeList().at(index.row())->titleHint();
    else
        return QVariant();
}

Qt::ItemFlags dtkMonitoringModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsEnabled;

    if (index.isValid())
        return Qt::ItemIsDragEnabled | defaultFlags;
    else
        return  defaultFlags;
}
