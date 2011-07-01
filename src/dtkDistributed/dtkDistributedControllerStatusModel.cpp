/* dtkDistributedControllerStatusModel.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jul  1 13:48:10 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  1 13:54:05 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerStatusModel.h"

class dtkDistributedControllerStatusModelPrivate
{
public:
};

dtkDistributedControllerStatusModel::dtkDistributedControllerStatusModel(QObject *parent) : QAbstractItemModel(parent), d(new dtkDistributedControllerStatusModelPrivate)
{

}

dtkDistributedControllerStatusModel::~dtkDistributedControllerStatusModel(void)
{
    delete d;

    d = NULL;
}

int dtkDistributedControllerStatusModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return 0;
}

int dtkDistributedControllerStatusModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return 0;
}

QVariant dtkDistributedControllerStatusModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);

    return QVariant();
}

QModelIndex dtkDistributedControllerStatusModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);

    return QModelIndex();
}

QModelIndex dtkDistributedControllerStatusModel::parent(const QModelIndex& index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}
