/* dtkComposerGraphView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:42:13 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:28:43 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <QtGui>
#include <QtWidgets>

class dtkComposerGraphViewPrivate;

class  dtkComposerGraphView : public QGraphicsView
{
    Q_OBJECT

public:
     dtkComposerGraphView(QWidget *parent = 0);
    ~dtkComposerGraphView(void);

private:
    dtkComposerGraphViewPrivate *d;
};

