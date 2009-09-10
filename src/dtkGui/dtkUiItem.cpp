/* dtkUiItem.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jun 12 17:35:14 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun 12 17:36:27 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkUiItem.h"

dtkUiItem::dtkUiItem(const QString& text, dtkUiItem::ItemType itemType, const QVariant& data) : QStandardItem(text)
{
    setEditable(false);
    setData(itemType, Qt::UserRole + 2);
    setData(data, Qt::UserRole + 1);
}

dtkUiItem::dtkUiItem(const QIcon& icon, const QString& text, dtkUiItem::ItemType itemType, const QVariant& data) : QStandardItem(icon, text)
{
    setEditable(false);
    setData(itemType, Qt::UserRole + 2);
    setData(data, Qt::UserRole + 1);
}

dtkUiItem::~dtkUiItem(void)
{

}

dtkUiItem::ItemType dtkUiItem::itemType(void) const
{
    return((dtkUiItem::ItemType) data(Qt::UserRole + 2).toInt());
}

void dtkUiItem::setItemType(dtkUiItem::ItemType itemType)
{
    setData(itemType, Qt::UserRole + 2);
}
