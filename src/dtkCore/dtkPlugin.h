/* dtkPlugin.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 13:49:50 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Apr 16 10:41:10 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 65
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTPLUGIN_H
#define DTKABSTRACTPLUGIN_H

#include "dtkAbstractObject.h"
#include "dtkCoreExport.h"
#include "dtkGlobal.h"

class dtkPluginPrivate;

class DTKCORE_EXPORT dtkPlugin : public dtkAbstractObject
{
    Q_OBJECT

public:
     dtkPlugin(QObject *parent = 0);
    ~dtkPlugin(void);
    
    virtual bool initialize(void) = 0;
    virtual bool uninitialize(void) = 0;
    
    virtual QString contact(void) const;
    virtual QString description(void) const = 0;
    virtual QString name(void) const = 0;
    virtual QString version(void) const;

    virtual QStringList authors(void) const;
    virtual QStringList contributors(void) const;
    virtual QStringList dependencies(void) const;
    virtual QStringList tags(void) const = 0;
    virtual QStringList types(void) const = 0;

private:
    dtkPluginPrivate *d;
};

Q_DECLARE_INTERFACE(dtkPlugin, "fr.inria.dtk/0.1.0")

#endif
