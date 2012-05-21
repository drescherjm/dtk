/* dtkViewLayoutItem.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:35 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 21 16:27:26 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 43
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVIEWLAYOUTITEM_H
#define DTKVIEWLAYOUTITEM_H

#include "dtkGuiExport.h"

#include <QtGui/QFrame>

class dtkViewLayout;
class dtkViewLayoutItemPrivate;

// /////////////////////////////////////////////////////////////////
// dtkViewLayoutItemProxy
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkViewLayoutItemProxy : public QFrame
{
    Q_OBJECT

public:
     dtkViewLayoutItemProxy(QWidget *parent = 0);
    ~dtkViewLayoutItemProxy(void);

signals:
    void focusedIn(void);
    void focusedOut(void);

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
};

// /////////////////////////////////////////////////////////////////
// dtkViewLayoutItem
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkViewLayoutItem : public QFrame
{
    Q_OBJECT

public:
     dtkViewLayoutItem(dtkViewLayoutItem *parent = 0);
    ~dtkViewLayoutItem(void);

public:
    dtkViewLayoutItem *parent(void);

public:
    dtkViewLayout *layout(void);

public:
    dtkViewLayoutItemProxy *proxy(void);

public:
    void setLayout(dtkViewLayout *layout);

public slots:
    void   split(void);
    void unsplit(void);

protected slots:
    void close(void);
    void horzt(void);
    void vertc(void);

protected slots:
    void onFocusedIn(void);
    void onFocusedOut(void);

protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dragLeaveEvent(QDragLeaveEvent *);
    void dropEvent(QDropEvent *);

private:
     dtkViewLayoutItemPrivate *d;

private:
     friend class dtkViewLayoutItemPrivate;
};

#endif
