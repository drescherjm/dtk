/* dtkComposerCompass.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 18 09:35:33 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 17 10:28:18 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 52
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtGui>
#include <QtWidgets>

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

