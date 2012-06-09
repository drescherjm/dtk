/* tstSidePane.h ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  8 09:38:45 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Jun 10 00:38:47 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTSIDEPANE_H
#define TSTSIDEPANE_H

#include <QtGui/QFrame>

class tstSidePanePrivate;

class tstSidePane : public QFrame
{
    Q_OBJECT

public:
     tstSidePane(QWidget *parent = 0);
    ~tstSidePane(void);

signals:
    void backgroundColorChanged(const QColor& color);
    void foregroundColorChanged(const QColor& color);

signals:
    void curveRenderModeChanged(int);

signals:
    void activatePanning(bool);
    void activateZooming(bool);

signals:
    void zoomForward(void);
    void zoomBackward(void);

public slots:
    void setZoomForwardEnabled(bool);
    void setZoomBackwardEnabled(bool);

private:
    tstSidePanePrivate *d;
};

#endif
