/* dtkPlotScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 10:31:41 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 14:45:14 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 82
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotCurve.h"
#include "dtkPlotData.h"
#include "dtkPlotScene.h"

class dtkPlotScenePrivate
{
public:
    QList<dtkPlotCurve *> curves;
    QList<dtkPlotData *> datas;
};

dtkPlotScene::dtkPlotScene(QObject *parent) : QGraphicsScene(parent), d(new dtkPlotScenePrivate)
{

}

dtkPlotScene::~dtkPlotScene(void)
{
    delete d;

    d = NULL;
}

dtkPlotScene& dtkPlotScene::operator<<(dtkPlotCurve *curve)
{
    this->addItem(curve);

    curve->setZValue(-1);

    d->curves << curve;
    
    return *(this);
}

dtkPlotScene& dtkPlotScene::operator<<(dtkPlotData *data)
{
    this->addItem(data);

    d->datas << data;
    
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


    if(l < 0.0)
        painter->drawLine(QPointF(l, 0.0), QPointF(0.0, 0.0));

    if(r > 0.0)
        painter->drawLine(QPointF(0.0, 0.0), QPointF(r, 0.0));

    if(-b < 0.0)
        painter->drawLine(QPointF(0.0, b), QPointF(0.0, 0.0));

    if(-t > 0.0)
        painter->drawLine(QPointF(0.0, 0.0), QPointF(0.0, t));

    if(-t > 0.0) {
        QPolygon tArrow;
        tArrow << QPoint(0.0, t);
        tArrow << QPoint(0.0, t) + QPoint(-5, +5);
        tArrow << QPoint(0.0, t) + QPoint(+5, +5);

        painter->drawConvexPolygon(tArrow);
    }

    if(r > 0.0) {
        QPolygon rArrow;
        rArrow << QPoint(r, 0.0);
        rArrow << QPoint(r, 0.0) + QPoint(-5, -5);
        rArrow << QPoint(r, 0.0) + QPoint(-5, +5);

        painter->drawConvexPolygon(rArrow);
    }
}

void dtkPlotScene::drawForeground(QPainter *painter, const QRectF& rect)
{
    // painter->setPen(Qt::NoPen);
    // painter->setBrush(QColor(19, 19, 19, 128));
    // painter->drawRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), 20);
}
