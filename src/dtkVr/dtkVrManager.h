/* dtkVrManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 10:07:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May  9 14:43:09 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 33
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

    void setStereo(bool stereo);

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
