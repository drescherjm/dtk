/* dtkInsetMenu.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jun  2 13:29:19 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun  3 11:55:20 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINSETMENU_H
#define DTKINSETMENU_H

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkInsetMenuPixmap
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuPixmapPrivate;

class dtkInsetMenuPixmap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
     dtkInsetMenuPixmap(const QPixmap& pixmap, QGraphicsItem *parent = 0);
    ~dtkInsetMenuPixmap(void);

    void setIndex(int index);
    void setFlag(int flag);

signals:
    void toggled(int index, int flag, bool checked);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    dtkInsetMenuPixmapPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkInsetMenuScroller
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuScrollerPrivate;

class dtkInsetMenuScroller : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
     dtkInsetMenuScroller(QGraphicsItem *parent = 0);
    ~dtkInsetMenuScroller(void);

    enum Type {
        None,
        Both,
        Left,
        Right
    };

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void setCount(int count);
    void setType(Type type);

    void reset(void);
    void incr(void);
    void decr(void);

signals:
    void scrollLeft(void);
    void scrollRight(void);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    dtkInsetMenuScrollerPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkInsetMenuHeader
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuHeaderPrivate;

class dtkInsetMenuHeader : public QFrame
{
    Q_OBJECT

public:
     dtkInsetMenuHeader(QWidget *parent);
    ~dtkInsetMenuHeader(void);

    int addTab(const QString& name);

signals:
    void buttonClicked(int);

private:
    dtkInsetMenuHeaderPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkInsetMenuBody
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuBodyPrivate;

class dtkInsetMenuBody : public QFrame
{
    Q_OBJECT

public:
     dtkInsetMenuBody(QWidget *parent);
    ~dtkInsetMenuBody(void);

    int addItem(int tab, const QPixmap& pixmap);

public slots:
    void clear(void);
    void update(void);
    void scrollLeft(void);
    void scrollRight(void);
    void setCurrentIndex(int index);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    dtkInsetMenuBodyPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkInsetMenu
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuPrivate;

class dtkInsetMenu : public QFrame
{
    Q_OBJECT

public:
     dtkInsetMenu(QWidget *parent);
    ~dtkInsetMenu(void);

    enum Style {
        dtkInsetMenuStyleDefault,
        dtkInsetMenuStyleBlue,
        dtkInsetMenuStyleGreen,
    };

    QSize sizeHint(void) const;

    int addTab(const QString& name);
    int addItem(int tab, const QPixmap& pixmap);

    void setStyle(Style style);

private:
    dtkInsetMenuPrivate *d;
};

#endif
