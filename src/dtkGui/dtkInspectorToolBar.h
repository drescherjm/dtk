/* dtkInspectorToolBar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 13 22:46:50 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 14:49:17 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINSPECTORTOOLBAR_H
#define DTKINSPECTORTOOLBAR_H

#include <QtGui/QToolBar>

#include "dtkGuiExport.h"

class dtkInspectorToolBarPrivate;

class DTKGUI_EXPORT dtkInspectorToolBar : public QWidget
{
    Q_OBJECT

public:
     dtkInspectorToolBar(QWidget *parent = 0);
    ~dtkInspectorToolBar(void);

    QSize sizeHint(void) const;

public:
    void addAction(QAction *action);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    dtkInspectorToolBarPrivate *d;
};

#endif
