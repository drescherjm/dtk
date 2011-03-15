/* dtkInspectorButton.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 13 21:36:11 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 14:53:17 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINSPECTORBUTTON_H
#define DTKINSPECTORBUTTON_H

#include <QtGui/QWidget>

#include "dtkGuiExport.h"

class dtkInspectorButtonPrivate;

class DTKGUI_EXPORT dtkInspectorButton : public QWidget
{
    Q_OBJECT

public:
     dtkInspectorButton(QWidget *parent = 0);
    ~dtkInspectorButton(void);

    QSize sizeHint(void) const;

signals:
    void clicked(void);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    dtkInspectorButtonPrivate *d;
};

#endif
