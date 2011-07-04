/* dtkDistributedControllerStatusModel.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 29 11:21:32 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  1 17:08:12 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 33
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERSTATUSMODEL_H
#define DTKDISTRIBUTEDCONTROLLERSTATUSMODEL_H

#include <QtGui>

class dtkDistributedController;
class dtkDistributedControllerStatusModelPrivate;

class dtkDistributedControllerStatusModel : public QAbstractItemModel
{
    Q_OBJECT

public:
     dtkDistributedControllerStatusModel(QObject *parent = 0);
    ~dtkDistributedControllerStatusModel(void);

public:
    void setController(dtkDistributedController *controller);

public slots:
    void update(void);

public:
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    dtkDistributedControllerStatusModelPrivate *d;
};

#endif
