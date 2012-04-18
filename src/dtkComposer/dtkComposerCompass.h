/* dtkComposerCompass.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 18 09:35:33 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 18 17:57:23 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 36
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERCOMPASS_H
#define DTKCOMPOSERCOMPASS_H

#include "dtkComposerExport.h"

#include <QtGui>

class dtkComposerCompassPrivate;
class dtkComposerView;

class DTKCOMPOSER_EXPORT dtkComposerCompass : public QGraphicsView
{
    Q_OBJECT

public:
     dtkComposerCompass(QWidget *parent = 0);
    ~dtkComposerCompass(void);

public:
    void setView(dtkComposerView *view);

protected:
    void paintEvent(QPaintEvent *event);

private:
    dtkComposerCompassPrivate *d;
};

#endif
