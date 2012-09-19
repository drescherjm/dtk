/* dtkViewLayoutItem.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:35 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 23 19:51:34 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 60
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

class dtkAbstractView;

class dtkViewLayout;
class dtkViewLayoutItemPrivate;

// /////////////////////////////////////////////////////////////////
// dtkViewLayoutItemProxy
// /////////////////////////////////////////////////////////////////

class dtkViewLayoutItemProxyPrivate;

class DTKGUI_EXPORT dtkViewLayoutItemProxy : public QFrame
{
    Q_OBJECT

public:
     dtkViewLayoutItemProxy(QWidget *parent = 0);
    ~dtkViewLayoutItemProxy(void);

public:
    dtkAbstractView *view(void);

public:
    void setView(dtkAbstractView *view);

signals:
    void focusedIn(void);
    void focusedOut(void);

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private:
    dtkViewLayoutItemProxyPrivate *d;
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
    void   clear(void);
    void   split(void);
    void unsplit(void);
    void maximize(void);

signals:
    void focused(dtkAbstractView *view);

protected slots:
    void close(void);
    void horzt(void);
    void vertc(void);
    void maxmz(void);

protected slots:
    void onFocusedIn(void);
    void onFocusedOut(void);

protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dragLeaveEvent(QDragLeaveEvent *);
    void dropEvent(QDropEvent *);

private:
    void notify(dtkAbstractView *view);

private:
     dtkViewLayoutItemPrivate *d;

private:
     friend class dtkViewLayoutItemPrivate;
     friend class dtkViewLayoutItemProxy;
};

#endif
