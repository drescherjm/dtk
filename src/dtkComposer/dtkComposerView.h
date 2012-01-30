/* dtkComposerView.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:00:30
 * Version: $Id$
 * Last-Updated: Mon Jan 30 15:12:12 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERVIEW_H
#define DTKCOMPOSERVIEW_H

#include "dtkComposerExport.h"

#include <QtGui>

class dtkComposerViewPrivate;

class DTKCOMPOSER_EXPORT dtkComposerView : public QGraphicsView
{
    Q_OBJECT

public:
             dtkComposerView(QWidget *parent = 0);
    virtual ~dtkComposerView(void);

private:
    dtkComposerViewPrivate *d;
};

#endif
