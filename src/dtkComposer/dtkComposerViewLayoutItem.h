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

#include "dtkComposerExport.h"

#include <QtWidgets/QFrame>

class dtkComposerViewLayout;
class dtkComposerViewLayoutItemPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerViewLayoutItemProxy
// /////////////////////////////////////////////////////////////////

class dtkComposerViewLayoutItemProxyPrivate;

class DTKCOMPOSER_EXPORT dtkComposerViewLayoutItemProxy : public QFrame
{
    Q_OBJECT

public:
     dtkComposerViewLayoutItemProxy(QWidget *parent = 0);
    ~dtkComposerViewLayoutItemProxy(void);

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
    dtkComposerViewLayoutItemProxyPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerViewLayoutItem
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerViewLayoutItem : public QFrame
{
    Q_OBJECT

public:
     dtkComposerViewLayoutItem(dtkComposerViewLayoutItem *parent = 0);
    ~dtkComposerViewLayoutItem(void);

public:
    QWidget *view(void);

public:
    dtkComposerViewLayoutItem *parent(void);
    dtkComposerViewLayoutItem *first(void);
    dtkComposerViewLayoutItem *second(void);

public:
    void setOrientation(Qt::Orientation orientation);
    void setSizes(QList<int> sizes);

public:
    int canvasHeight(void);
    int footerHeight(void);
    int handleHeight(void);
    int handleWidth(void);

public:
    dtkComposerViewLayout *layout(void);

public:
    dtkComposerViewLayoutItemProxy *proxy(void);

public:
    void setLayout(dtkComposerViewLayout *layout);

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
     dtkComposerViewLayoutItemPrivate *d;

private:
     friend class dtkComposerViewLayoutItemPrivate;
     friend class dtkComposerViewLayoutItemProxy;
};

//
// dtkComposerViewLayoutItem.h ends here
