/* dtkViewManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:37:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jan 16 17:22:17 2014 (+0100)
 *           By: Selim Kraria
 *     Update #: 14
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
    void hideCurrentWidget(void);
    
private:
    dtkViewManagerPrivate *d;
};

#endif
