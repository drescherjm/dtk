/* dtkDistributorInset.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar 25 13:10:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 31 19:11:05 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 77
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTORINSET_H
#define DTKDISTRIBUTORINSET_H

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetPixmap
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetPixmapPrivate;

class dtkDistributorInsetPixmap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
     dtkDistributorInsetPixmap(const QPixmap& pixmap, QGraphicsItem *parent = 0);
    ~dtkDistributorInsetPixmap(void);

    void setIndex(int index);
    void setFlag(int flag);

signals:
    void toggled(int index, int flag, bool checked);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    dtkDistributorInsetPixmapPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetScroller
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetScrollerPrivate;

class dtkDistributorInsetScroller : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
     dtkDistributorInsetScroller(QGraphicsItem *parent = 0);
    ~dtkDistributorInsetScroller(void);

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
    dtkDistributorInsetScrollerPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetHeader
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetHeader : public QFrame
{
    Q_OBJECT

public:
     dtkDistributorInsetHeader(QWidget *parent);
    ~dtkDistributorInsetHeader(void);

signals:
    void buttonClicked(int);
};

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetBody
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetBodyPrivate;

class dtkDistributorInsetBody : public QFrame
{
    Q_OBJECT

public:
     dtkDistributorInsetBody(QWidget *parent);
    ~dtkDistributorInsetBody(void);

public slots:
    void clear(void);
    void update(void);
    void scrollLeft(void);
    void scrollRight(void);
    void setCurrentIndex(int index);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    dtkDistributorInsetBodyPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributorInset
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetPrivate;

class dtkDistributorInset : public QFrame
{
    Q_OBJECT

public:
     dtkDistributorInset(QWidget *parent);
    ~dtkDistributorInset(void);

private:
    dtkDistributorInsetPrivate *d;
};

#endif
