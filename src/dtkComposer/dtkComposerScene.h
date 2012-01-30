/* dtkComposerScene.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:11:39
 * Version: $Id$
 * Last-Updated: Mon Jan 30 18:38:44 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERSCENE_H
#define DTKCOMPOSERSCENE_H

#include "dtkComposerExport.h"

#include <QtGui>

class dtkComposerScenePort;
class dtkComposerScenePrivate;

class DTKCOMPOSER_EXPORT dtkComposerScene : public QGraphicsScene
{
    Q_OBJECT

public:
             dtkComposerScene(QObject *parent = 0);
    virtual ~dtkComposerScene(void);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

protected:
    dtkComposerScenePort *portAt(const QPointF& point) const;

private:
    dtkComposerScenePrivate *d;
};

#endif
