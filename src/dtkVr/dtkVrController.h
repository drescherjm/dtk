/* dtkVrController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  6 11:56:21 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  9 13:15:09 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRCONTROLLER_H
#define DTKVRCONTROLLER_H

#include <QtCore>

class dtkAbstractView;

class dtkVrControllerPrivate;

class dtkVrController : public QObject
{
    Q_OBJECT

public:
    static dtkVrController *instance(void);

    void setTracker(const QUrl& url);
    void setDevice(const QUrl& url);

    void assign(dtkAbstractView *view);

protected slots:
    void onButtonPressed(int button);
    void onButtonReleased(int button);

protected:
     dtkVrController(void);
    ~dtkVrController(void);

private:
    static dtkVrController *s_instance;

private:
    dtkVrControllerPrivate *d;
};

#endif
