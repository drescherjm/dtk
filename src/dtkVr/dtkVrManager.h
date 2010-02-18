/* dtkVrManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 10:07:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 10:24:14 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRMANAGER_H
#define DTKVRMANAGER_H

#include "dtkVrExport.h"

#include <QtCore>

class dtkVrProcess;
class dtkVrManagerPrivate;

class DTKVR_EXPORT dtkVrManager : public QObject
{
    Q_OBJECT

public:
    static dtkVrManager *instance(void);

    void   initialize(void);
    void uninitialize(void);

    dtkVrProcess *create(QString type);

protected:
    static dtkVrManager *s_instance;

private:
     dtkVrManager(void);
    ~dtkVrManager(void);

private:
    dtkVrManagerPrivate *d;
};

#endif
