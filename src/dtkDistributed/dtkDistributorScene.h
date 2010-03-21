/* dtkDistributorScene.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 18:29:30 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 22:19:10 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTORSCENE_H
#define DTKDISTRIBUTORSCENE_H

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkDistributorLabel
// /////////////////////////////////////////////////////////////////

class dtkDistributorLabel : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF position READ pos WRITE setPos)

public:
     dtkDistributorLabel(QGraphicsItem *parent = 0);
    ~dtkDistributorLabel(void);

    void setPixmap(const QPixmap& pixmap);
};

// /////////////////////////////////////////////////////////////////
// dtkDistributorButton
// /////////////////////////////////////////////////////////////////

class dtkDistributorButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
     dtkDistributorButton(QGraphicsItem *parent = 0);
    ~dtkDistributorButton(void);

    void setPixmapNormal(const QPixmap& pixmap);
    void setPixmapPressed(const QPixmap& pixmap);

signals:
    void clicked(void);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QPixmap pixmap_normal;
    QPixmap pixmap_pressed;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributorScene
// /////////////////////////////////////////////////////////////////

class dtkDistributorScenePrivate;

class dtkDistributorScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected WRITE setConnected)

public:
     dtkDistributorScene(void);
    ~dtkDistributorScene(void);

    bool connected(void);
    void setConnected(bool connected);

protected:
    void drawBackground(QPainter *painter, const QRectF& rect);

private:
    dtkDistributorScenePrivate *d;
};

#endif
