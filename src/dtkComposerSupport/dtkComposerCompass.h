/* dtkComposerCompass.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 18 09:35:33 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 19 13:16:43 2012 (+0200)
 *           By: tkloczko
 *     Update #: 46
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERCOMPASS_H
#define DTKCOMPOSERCOMPASS_H

#include "dtkComposerSupportExport.h"

#include <QtWidgets>

class dtkComposerCompassPrivate;
class dtkComposerView;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerCompass : public QGraphicsView
{
    Q_OBJECT

public:
    dtkComposerCompass(QWidget *parent = 0);
    ~dtkComposerCompass(void);

public:
    void setView(dtkComposerView *view);

public slots:
    void update(void);

protected:
    void paintEvent(QPaintEvent *event);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    dtkComposerCompassPrivate *d;
};

#endif
