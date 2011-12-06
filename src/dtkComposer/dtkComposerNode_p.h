/* dtkComposerNode_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Dec  6 16:03:06 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec  6 16:04:07 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODE_P_H
#define DTKCOMPOSERNODE_P_H

#include "dtkComposerNode.h"

class dtkComposerNodePrivate
{
public:
    QRectF ghostRect(void);

public:
    dtkComposerNode *q;

    qreal penWidth;
    qreal header_height;
    qreal node_radius;
    qreal margin_left;
    qreal margin_right;
    qreal margin_top;
    qreal margin_bottom;

    QGraphicsTextItem *title;

    QString name;

    dtkComposerNodeProperty *clicked_property;

    dtkComposerNode::Attribute attribute;
    dtkComposerNode::Kind kind;

    QString type;

    dtkAbstractObject *object;

    QList<QAction *> actions;

    bool active;
    bool dirty;
    bool ghost;
    bool resizable;

          dtkComposerNode *  parent;
    QList<dtkComposerNode *> children;

    int count;

    QPointF ghost_position;
    QPointF non_ghost_position;

public:
    QPointF drag_point;
    QRectF bounding_rect;

    QColor pen_color;
    QPen pen;
};

#endif
