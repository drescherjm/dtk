/* dtkPlotScene.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 10:29:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 14:18:47 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTSCENE_H
#define DTKPLOTSCENE_H

#include <QtGui>

class dtkPlotCurve;
class dtkPlotData;
class dtkPlotScenePrivate;

class dtkPlotScene : public QGraphicsScene
{
    Q_OBJECT

public:
     dtkPlotScene(QObject *parent = 0);
    ~dtkPlotScene(void);

    dtkPlotScene& operator<<(dtkPlotCurve *curve);
    dtkPlotScene& operator<<(dtkPlotData *data);

protected:
    void drawBackground(QPainter *painter, const QRectF& rect);
    void drawForeground(QPainter *painter, const QRectF& rect);

private:
    dtkPlotScenePrivate *d;
};

#endif
