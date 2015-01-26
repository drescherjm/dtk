/* dtkComposerGraphView.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:42:13 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtWidgets>

class dtkComposerGraphViewPrivate;

class DTKCOMPOSER_EXPORT dtkComposerGraphView : public QGraphicsView
{
    Q_OBJECT

public:
     dtkComposerGraphView(QWidget *parent = 0);
    ~dtkComposerGraphView(void);

private:
    dtkComposerGraphViewPrivate *d;
};

