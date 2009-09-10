/* dtkUiItemDelegate.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jun 12 19:06:32 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun 12 19:06:44 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKUIITEMDELEGATE_H
#define DTKUIITEMDELEGATE_H

#include <QItemDelegate>

class dtkUiItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
     dtkUiItemDelegate(QObject *parent = 0);
    ~dtkUiItemDelegate(void);

    void paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
    
private:
    void       drawValue(QPainter *painter, int x, int y, int w, int h, int itemType, QVariant& value) const;
    void   drawBoolValue(QPainter *painter, int y, int w, int h, bool value) const;
    void drawStringValue(QPainter *painter, int y, int w, int h, const QString& value) const;
    void   drawLinkValue(QPainter *painter, int y, int w, int h) const;
};

#endif
