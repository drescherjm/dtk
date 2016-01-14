#ifndef DTKMONITORINGMODEL_H
#define DTKMONITORINGMODEL_H


#include <QAbstractListModel>
#include <QVariant>

#include <dtkMonitoringController>
#include <dtkComposer/dtkComposerNode>

#include "dtkMonitoringExport.h"

class dtkMonitoringModelPrivate;

class DTKMONITORING_EXPORT dtkMonitoringModel : public QAbstractListModel
{
    Q_OBJECT
public:
     dtkMonitoringModel();
    ~dtkMonitoringModel();

public:
    int  rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;


private:
    dtkMonitoringModelPrivate* d;

};

#endif // DTKMONITORINGMODEL_H
