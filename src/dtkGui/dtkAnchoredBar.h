/* dtkAnchoredBar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 16 08:43:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar 16 08:45:38 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKANCHOREDBAR_H
#define DTKANCHOREDBAR_H

#include <QtGui>

class dtkAnchoredBar : public QToolBar
{
    Q_OBJECT

public:
    dtkAnchoredBar(QWidget *parent = 0);

    QSize sizeHint(void) const;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint dragPosition;
    int parentHeight;
    int parentWidth;
};

#endif
