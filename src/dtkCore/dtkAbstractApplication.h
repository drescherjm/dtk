/* dtkAbstractApplication.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/04 12:01:21
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkCoreExport.h"
#include <dtkLog>

#include <QtCore>

class dtkAbstractApplicationPrivate;

class DTKCORE_EXPORT dtkAbstractApplication
{
public:
             dtkAbstractApplication(void);
    virtual ~dtkAbstractApplication(void);

public:
    virtual void initialize(void);

public:
    bool noGui(void);

public:
    void setApplicationName(const QString& name);
    void setApplicationVersion(const QString& version);
    void setOrganizationName(const QString& name);
    void setOrganizationDomain(const QString& name);

public:
    QString applicationName(void);

public:
    QCommandLineParser  *parser(void);
    QSettings         *settings(void);

private:
    dtkAbstractApplicationPrivate *d;

};




