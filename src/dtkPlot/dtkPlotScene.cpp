/* dtkPlotScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 10:31:41 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 22 13:00:01 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 60
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotPoint.h"
#include "dtkPlotScene.h"

class dtkPlotScenePrivate
{
public:
    QList<dtkPlotPoint *> points;
};

dtkPlotScene::dtkPlotScene(QObject *parent) : QGraphicsScene(parent), d(new dtkPlotScenePrivate)
{

}

dtkPlotScene::~dtkPlotScene(void)
{
    delete d;

    d = NULL;
}

dtkPlotScene& dtkPlotScene::operator<<(dtkPlotPoint *point)
{
    this->addItem(point);

    d->points << point;
    
    return *(this);
}

void dtkPlotScene::drawBackground(QPainter *painter, const QRectF& rect)
{
    QPointF bl = this->sceneRect().bottomLeft();
    QPointF tl = this->sceneRect().topLeft();
    QPointF br = this->sceneRect().bottomRight();
    QPointF tr = this->sceneRect().topRight();

    qreal l = bl.x();
    qreal r = br.x();
    qreal t = tr.y();
    qreal b = br.y();

    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawLine(QPointF(l, 0.0), QPointF(0.0, 0.0));
    painter->drawLine(QPointF(0.0, 0.0), QPointF(r, 0.0));
    painter->drawLine(QPointF(0.0, b), QPointF(0.0, 0.0));
    painter->drawLine(QPointF(0.0, 0.0), QPointF(0.0, t));

    QPolygon tArrow;
    tArrow << QPoint(0.0, t);
    tArrow << QPoint(0.0, t) + QPoint(-5, +5);
    tArrow << QPoint(0.0, t) + QPoint(+5, +5);

    painter->drawConvexPolygon(tArrow);

    QPolygon rArrow;
    rArrow << QPoint(r, 0.0);
    rArrow << QPoint(r, 0.0) + QPoint(-5, -5);
    rArrow << QPoint(r, 0.0) + QPoint(-5, +5);

    painter->drawConvexPolygon(rArrow);
}

void dtkPlotScene::drawForeground(QPainter *painter, const QRectF& rect)
{
    // painter->setPen(Qt::NoPen);
    // painter->setBrush(QColor(19, 19, 19, 128));
    // painter->drawRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), 20);
}
