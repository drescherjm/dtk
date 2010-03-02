/* dtkVrManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 10:07:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  2 14:10:19 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 32
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

    void setTracker(const QUrl& url);
    void setDevice(const QUrl& url);
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
