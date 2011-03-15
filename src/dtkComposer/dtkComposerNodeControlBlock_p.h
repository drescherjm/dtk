/* dtkComposerNodeControlBlock_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar  8 13:31:11 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  8 15:03:27 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 27
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
    dtkComposerNodeControlBlockButton *button;
    dtkComposerNodeControlBlockLabel *label;

public:
    QList<dtkComposerNodeProperty *>  input_properties;
    QList<dtkComposerNodeProperty *> output_properties;

public:
    bool interactive;
    QColor pen_color;
    QColor brush_color;
    QString title;
};

#endif
