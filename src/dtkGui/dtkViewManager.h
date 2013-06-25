/* dtkViewManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:37:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 25 10:08:50 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 13
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

class dtkAbstractView;
class dtkViewManagerPrivate;

class DTKGUI_EXPORT dtkViewManager : public QFrame
{
    Q_OBJECT

public:
     dtkViewManager(QWidget *parent = 0);
    ~dtkViewManager(void);

public:
    void addWidget(QWidget *widget);
    void setCurrentWidget(QWidget *widget);

signals:
    void focused(dtkAbstractView *view);

public slots:
    void clear(void);
    
private:
    dtkViewManagerPrivate *d;
};

#endif
