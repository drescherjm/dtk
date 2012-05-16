/* dtkViewLayoutItem.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:35 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:38:39 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVIEWLAYOUTITEM_H
#define DTKVIEWLAYOUTITEM_H

#include <QFrame>

class dtkViewLayout;
class dtkViewLayoutItemPrivate;

class dtkViewLayoutItem : public QFrame
{
    Q_OBJECT

public:
     dtkViewLayoutItem(dtkViewLayoutItem *parent = 0);
    ~dtkViewLayoutItem(void);
    
public:
     void setCurrent(dtkViewLayoutItem *item);

protected slots:
     void close(void);
     void horzt(void);
     void vertc(void);

protected:
     void remove(dtkViewLayoutItem *item);

protected:
     void focusInEvent(QFocusEvent *);
     void focusOutEvent(QFocusEvent *);

protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dragLeaveEvent(QDragLeaveEvent *);
    void dropEvent(QDropEvent *);

private:
     friend class dtkViewLayoutItemPrivate;

private:
     dtkViewLayoutItemPrivate *d;
};

#endif
