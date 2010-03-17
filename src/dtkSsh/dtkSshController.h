/* dtkSshController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 16 14:50:21 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 17 08:45:38 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSSHCONTROLLER_H
#define DTKSSHCONTROLLER_H

#include <QtCore>

class dtkSshControllerPrivate;

class dtkSshController : public QObject
{
    Q_OBJECT

public:
    static dtkSshController *instance(void);

    bool createConnection(const QUrl& host);
    bool closeConnection(void);

    bool execute(const QString& command, QString& output);

protected:
     dtkSshController(void);
    ~dtkSshController(void);

protected:
    static dtkSshController *s_instance;

private:
    dtkSshControllerPrivate *d;
};

#endif
