/* dtkUiItem.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jun 12 17:34:16 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jul  8 21:15:55 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKUIITEM_H
#define DTKUIITEM_H

#include <QStandardItem>

#include "dtkGuiExport.h"

class DTKGUI_EXPORT dtkUiItem : public QStandardItem
{
public:
    enum ItemType { Button, Link, Group, Value, MultiValue, Info };
    
public:
     dtkUiItem(const QString& text, ItemType itemType, const QVariant& data = QVariant());
     dtkUiItem(const QIcon& icon, const QString& text, ItemType itemType, const QVariant& data = QVariant());
    ~dtkUiItem(void);
    
    ItemType itemType(void) const;

    void setItemType(ItemType itemType);
};

#endif
