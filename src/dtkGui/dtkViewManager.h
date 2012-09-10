/* dtkViewManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:37:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:45:54 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVIEWMANAGER_H
#define DTKVIEWMANAGER_H

#include "dtkGuiExport.h"

#include <QtGui/QFrame>

class dtkViewManagerPrivate;

class DTKGUI_EXPORT dtkViewManager : public QFrame
{
    Q_OBJECT

public:
     dtkViewManager(QWidget *parent = 0);
    ~dtkViewManager(void);
    
public slots:
    void clear(void);
    
private:
    dtkViewManagerPrivate *d;
};

#endif
