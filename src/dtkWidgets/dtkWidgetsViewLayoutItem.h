// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include "dtkWidgetsExport.h"

#include <QtWidgets/QFrame>

class dtkWidgetsViewLayout;
class dtkWidgetsViewLayoutItemPrivate;

// /////////////////////////////////////////////////////////////////
// dtkWidgetsViewLayoutItemProxy
// /////////////////////////////////////////////////////////////////

class dtkWidgetsViewLayoutItemProxyPrivate;

class DTKWIDGETS_EXPORT dtkWidgetsViewLayoutItemProxy : public QFrame
{
    Q_OBJECT

public:
     dtkWidgetsViewLayoutItemProxy(QWidget *parent = 0);
    ~dtkWidgetsViewLayoutItemProxy(void);

public:
    QWidget *view(void);

public:
    void setView(QWidget *view);

signals:
    void focusedIn(void);
    void focusedOut(void);

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private:
    dtkWidgetsViewLayoutItemProxyPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkWidgetsViewLayoutItem
// /////////////////////////////////////////////////////////////////

class DTKWIDGETS_EXPORT dtkWidgetsViewLayoutItem : public QFrame
{
    Q_OBJECT

public:
     dtkWidgetsViewLayoutItem(dtkWidgetsViewLayoutItem *parent = 0);
    ~dtkWidgetsViewLayoutItem(void);

public:
    QWidget *view(void);

public:
    dtkWidgetsViewLayoutItem *parent(void);
    dtkWidgetsViewLayoutItem *first(void);
    dtkWidgetsViewLayoutItem *second(void);

public:
    void setOrientation(Qt::Orientation orientation);
    void setSizes(QList<int> sizes);

public:
    int canvasHeight(void);
    int footerHeight(void);
    int handleHeight(void);
    int handleWidth(void);

public:
    dtkWidgetsViewLayout *layout(void);

public:
    dtkWidgetsViewLayoutItemProxy *proxy(void);

public:
    void setLayout(dtkWidgetsViewLayout *layout);

public slots:
    void   clear(void);
    void   split(void);
    void unsplit(void);
    void maximize(void);

signals:
    void focused(QWidget *view);
    void unfocused(QWidget *view);

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
    void notify(QWidget *view);

private:
     dtkWidgetsViewLayoutItemPrivate *d;

private:
     friend class dtkWidgetsViewLayoutItemPrivate;
     friend class dtkWidgetsViewLayoutItemProxy;
};

//
// dtkWidgetsViewLayoutItem.h ends here
