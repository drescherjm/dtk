/* dtkHelpController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 16:00:38 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 20:10:12 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 28
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

#include "dtkHelpExport.h"

class dtkHelpControllerPrivate;

class DTKHELP_EXPORT dtkHelpController : public QObject
{
    Q_OBJECT

public:
    static dtkHelpController *instance(void);

    void   initialize(void);
    void uninitialize(void);

    void  readSettings(void);
    void writeSettings(void);

    bool   registerDocumentation(const QString& path);
    bool unregisterDocumentation(const QString& namespaceName);

    QHelpEngine *engine(void);

    QUrl filter(const QUrl& url) const;

    QStringList registeredNamespaces(void) const;

protected:
     dtkHelpController(void);
    ~dtkHelpController(void);

private:
    static dtkHelpController *s_instance;

private:
    dtkHelpControllerPrivate *d;
};

#endif
