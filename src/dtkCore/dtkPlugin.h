/* dtkPlugin.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 13:49:50 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 14:43:47 2012 (+0200)
 *           By: tkloczko
 *     Update #: 69
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

class dtkAbstractDataFactory;
class dtkAbstractProcessFactory;
class dtkAbstractViewFactory;

class dtkPluginPrivate;

// /////////////////////////////////////////////////////////////////
// dtkPlugin interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkPlugin : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkPlugin(QObject *parent = 0);
             dtkPlugin(const dtkPlugin& other);
    virtual ~dtkPlugin(void);
    
public:
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

    void setViewFactorySingleton(dtkAbstractViewFactory *viewSingletonFactory);
    dtkAbstractViewFactory *viewFactorySingleton(void);

    void setDataFactorySingleton(dtkAbstractDataFactory *dataSingletonFactory);
    dtkAbstractDataFactory *dataFactorySingleton(void);

    void setProcessFactorySingleton(dtkAbstractProcessFactory *processSingletonFactory);
    dtkAbstractProcessFactory *processFactorySingleton(void);

private:
    DTK_DECLARE_PRIVATE(dtkPlugin);
};

Q_DECLARE_INTERFACE(dtkPlugin, "fr.inria.dtk/0.1.0")

#endif
