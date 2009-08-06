/* dtkCreatorViewer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 14:38:18 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 16:04:39 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCREATORVIEWER_H
#define DTKCREATORVIEWER_H

#include <QtGui/QWidget>

class dtkCreatorViewerPrivate;

class dtkCreatorViewer : public QWidget
{
    Q_OBJECT

public:
     dtkCreatorViewer(QWidget *parent = 0);
    ~dtkCreatorViewer(void);

    void attach(QWidget *view, int row = 0, int column = 0, int rspan = 1, int cspan = 1);

private:
   dtkCreatorViewerPrivate *d;
};

#endif
