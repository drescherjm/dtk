/* dtkPlotterMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 17 12:53:41 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 17 14:06:15 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTTERMAINWINDOW_H
#define DTKPLOTTERMAINWINDOW_H

class dtkPlotterMainWindowPrivate;

class dtkPlotterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     dtkPlotterMainWindow(QWidget *parent = 0);
    ~dtkPlotterMainWindow(void);

private:
    dtkPlotterMainWindowPrivate *d;
};

#endif
