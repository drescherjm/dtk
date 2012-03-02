/* dtkLogView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Mar  2 15:08:10 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar  2 15:15:35 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKLOGVIEW_H
#define DTKLOGVIEW_H

#include "dtkLogExport.h"

#include <QtGui>

class dtkLogViewPrivate;

class DTKLOG_EXPORT dtkLogView : public QWidget
{
    Q_OBJECT
        
public:
     dtkLogView(QWidget *parent = 0);
    ~dtkLogView(void);

private:
    dtkLogViewPrivate *d;
};

#endif
