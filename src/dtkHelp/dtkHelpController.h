/* dtkHelpController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 16:00:38 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb  6 13:30:41 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 12
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

    QString path(void) const;

protected:
     dtkHelpController(void);
    ~dtkHelpController(void);

private:
    static dtkHelpController *s_instance;

private:
    dtkHelpControllerPrivate *d;
};

#endif
