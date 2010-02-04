/* dtkHelpController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 16:00:38 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  3 17:23:47 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKHELPCONTROLLER_H
#define DTKHELPCONTROLLER_H

#include <QtCore>
#include <QtHelp>

class dtkHelpControllerPrivate;

class dtkHelpController : public QObject
{
    Q_OBJECT

public:
    static dtkHelpController *instance(void);

    void   initialize(void);
    void uninitialize(void);

    void  readSettings(void);
    void writeSettings(void);

    QHelpEngine *engine(void);

protected:
     dtkHelpController(void);
    ~dtkHelpController(void);

private:
    static dtkHelpController *s_instance;

private:
    dtkHelpControllerPrivate *d;
};

#endif
