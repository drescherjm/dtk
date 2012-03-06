/* dtkLogView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Mar  2 15:08:10 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar  5 14:27:11 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
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

public slots:
    void displayTrace(bool display);
    void displayDebug(bool display);
    void displayInfo(bool display);
    void displayWarn(bool display);
    void displayError(bool display);
    void displayFatal(bool display);

private:
    dtkLogViewPrivate *d;
};

#endif
