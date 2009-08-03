/* dtkAbstractDeviceFactory.h --- 
 * 
 * Author: Jean-Christophe Lombardo
 * Copyright (C) 2009 - Jean-Christophe Lombardo, Inria
 * Created: Fri Mar 20 17:03:37 2009
 * Version: $Id$
 * Last-Updated: Sat Aug  1 00:09:40 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDEVICEFACTORY_H
#define DTKABSTRACTDEVICEFACTORY_H

#include <dtkCore/dtkAbstractFactory.h>

class dtkAbstractDevice;
class dtkAbstractDeviceFactoryPrivate;

class DTKCORE_EXPORT dtkAbstractDeviceFactory : public dtkAbstractFactory
{
    Q_OBJECT

public:
    typedef dtkAbstractDevice *(*dtkAbstractDeviceCreator)(QString name);

    typedef QMap<QString, dtkAbstractDeviceCreator> dtkAbstractDeviceCreatorMap;
    
public:
    static dtkAbstractDeviceFactory *instance(void);

    bool registerDeviceType(QString type, dtkAbstractDeviceCreator func);

    QString names(QString type);

    dtkAbstractDevice *get(QString type, QString name);

public slots:
    dtkAbstractDevice *create(QString type, QString name);
    
protected:
     dtkAbstractDeviceFactory(void);
    ~dtkAbstractDeviceFactory(void);

private:
    static dtkAbstractDeviceFactory *s_instance;

private:
    dtkAbstractDeviceFactoryPrivate *d;
};

#endif

