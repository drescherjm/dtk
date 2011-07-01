/* dtkDistributedControllerStatusModel.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jul  1 13:48:10 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  1 15:13:18 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 51
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerStatusModel.h"
#include "dtkDistributedNode.h"

class dtkDistributedControllerStatusModelPrivate
{
public:
    dtkDistributedController *controller;
};

dtkDistributedControllerStatusModel::dtkDistributedControllerStatusModel(QObject *parent) : QAbstractItemModel(parent), d(new dtkDistributedControllerStatusModelPrivate)
{
    d->controller = NULL;
}

dtkDistributedControllerStatusModel::~dtkDistributedControllerStatusModel(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerStatusModel::setController(dtkDistributedController *controller)
{
    d->controller = controller;
}

int dtkDistributedControllerStatusModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return 6;
}

int dtkDistributedControllerStatusModel::rowCount(const QModelIndex& parent) const
{
    if (!d->controller)
        return 0;

    return d->controller->nodes().count();
}

QVariant dtkDistributedControllerStatusModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role);

    if (!d->controller)
        return QVariant();

    return d->controller->nodes().at(index.row())->name();
}

QModelIndex dtkDistributedControllerStatusModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);

    return createIndex(row, column);
}

QModelIndex dtkDistributedControllerStatusModel::parent(const QModelIndex& index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}
