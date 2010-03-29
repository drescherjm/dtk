/* dtkDistributorScene.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 18:29:30 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 29 09:44:48 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 47
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

class dtkDistributorLabelPrivate;

class dtkDistributorLabel : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(QPointF position READ pos WRITE setPos)

public:
     dtkDistributorLabel(QGraphicsItem *parent = 0);
    ~dtkDistributorLabel(void);

    void setLabel(const QString& label);
    void setPixmap(const QPixmap& pixmap);

protected:
    void layout(void);

private:
    dtkDistributorLabelPrivate *d;
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
// dtkDistributorCombo
// /////////////////////////////////////////////////////////////////

class dtkDistributorComboPrivate;

class dtkDistributorCombo : public QGraphicsProxyWidget
{
    Q_OBJECT
    Q_PROPERTY(QPointF position READ pos WRITE setPos)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
     dtkDistributorCombo(QGraphicsItem *parent = 0);
    ~dtkDistributorCombo(void);

    QString text(void) const;

private:
    dtkDistributorComboPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributorNode
// /////////////////////////////////////////////////////////////////

class dtkDistributedNode;
class dtkDistributorNodePrivate;

class dtkDistributorNode : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)

    Q_PROPERTY(QPointF position READ pos WRITE setPos)

public:
     dtkDistributorNode(dtkDistributedNode *node, QGraphicsItem *parent = 0);
    ~dtkDistributorNode(void);

protected:
    void layout(void);

private:
    dtkDistributorNodePrivate *d;
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
