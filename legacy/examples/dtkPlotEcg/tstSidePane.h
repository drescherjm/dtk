/* tstSidePane.h ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  8 09:38:45 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 27 12:02:15 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 23
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
    void activatePicking(bool);

private:
    tstSidePanePrivate *d;
};

#endif
