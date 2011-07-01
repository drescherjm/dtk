/* dtkDistributedControllerStatusModel.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 29 11:21:32 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  1 14:57:15 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 24
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

    void setController(dtkDistributedController *controller);

    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    
private:
    dtkDistributedControllerStatusModelPrivate *d;
};

#endif
