/* dtkComposerNodeControlBlock_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar  8 13:31:11 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Oct 25 15:33:41 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 43
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROLBLOCK_P_H
#define DTKCOMPOSERNODECONTROLBLOCK_P_H

#include <QtGui>

class dtkComposerNodeControl;
class dtkComposerNodeControlBlockButtonRemove;
class dtkComposerNodeControlBlockButton;
class dtkComposerNodeControlBlockLabel;
class dtkComposerNodeProperty;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlockPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlBlockPrivate
{
public:
    dtkComposerNodeControl *parent;

public:
    dtkComposerNodeControlBlockButtonRemove *remove_button;
    dtkComposerNodeControlBlockButton *button_add_left;
    dtkComposerNodeControlBlockButton *button_rem_left;
    dtkComposerNodeControlBlockButton *button_add_right;
    dtkComposerNodeControlBlockButton *button_rem_right;
    dtkComposerNodeControlBlockButton *button_add_both;
    dtkComposerNodeControlBlockButton *button_rem_both;
    dtkComposerNodeControlBlockLabel *label;

public:
    QList<dtkComposerNode *> nodes; 

    QList<dtkComposerNodeProperty *>  input_properties;
    QList<dtkComposerNodeProperty *> output_properties;

public:
    bool interactive;
    qreal height;
    qreal height_ratio;
    QColor pen_color;
    QColor brush_color;
    QString title;
};

#endif
