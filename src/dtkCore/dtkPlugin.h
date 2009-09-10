/* dtkPlugin.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 13:49:50 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Sep  9 08:49:05 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 43
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTPLUGIN_H
#define DTKABSTRACTPLUGIN_H

#include <dtkCore/dtkCoreExport.h>

#include <dtkCore/dtkGlobal.h>

class dtkPluginPrivate;

class DTKCORE_EXPORT dtkPlugin : public QObject 
{
    Q_OBJECT

public:
     dtkPlugin(QObject *parent = 0);
    ~dtkPlugin(void);
    
    virtual bool initialize(void) = 0;
    virtual bool uninitialize(void) = 0;
    
    virtual QString name(void) const = 0;
    virtual QString description(void) const = 0;

    virtual QStringList tags(void) const = 0;
    virtual QStringList types(void) const = 0;

private:
    dtkPluginPrivate *d;
};

Q_DECLARE_INTERFACE(dtkPlugin, "fr.inria.dtk/0.1.0")

#endif
