/* dtkAbstractPlugin.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 13:49:50 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  1 19:45:18 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 30
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

class dtkAbstractPluginPrivate;

class DTKCORE_EXPORT dtkAbstractPlugin : public QObject 
{
    Q_OBJECT

public:
     dtkAbstractPlugin(QObject *parent = 0);
    ~dtkAbstractPlugin(void);
    
    virtual bool initialize(void) = 0;
    virtual bool uninitialize(void) = 0;
    
    virtual QString id(void) const = 0;
    virtual QString url(void) const = 0;
    virtual QString name(void) const = 0;
    virtual QString license(void) const = 0;
    virtual QString version(void) const = 0;
    virtual QString copyright(void) const = 0;
    virtual QStringList authors(void) const = 0;
    virtual QString description(void) const = 0;
    virtual QStringList dependences(void) const = 0;
    virtual QStringList tags(void) const = 0;

    virtual QWidget *ui(void);
    
    bool isRunning(void) const;
    QString path(void) const;
    
    void setRunning(bool isRunning);
    void setPath(const QString & path);

private:
    dtkAbstractPluginPrivate *d;
};

#endif
