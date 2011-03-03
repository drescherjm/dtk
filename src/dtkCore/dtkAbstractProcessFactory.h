/* dtkAbstractProcessFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Jan 15 14:09:46 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 60
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTPROCESSFACTORY_H
#define DTKABSTRACTPROCESSFACTORY_H

#include <QtCore>

#include <dtkCore/dtkAbstractFactory.h>

class dtkAbstractProcess;
class dtkAbstractProcessFactoryPrivate;

class DTKCORE_EXPORT dtkAbstractProcessFactory : public dtkAbstractFactory
{
    Q_OBJECT

public:
    typedef dtkAbstractProcess *(*dtkAbstractProcessCreator)(void);

    typedef QHash<QString, dtkAbstractProcessCreator> dtkAbstractProcessCreatorHash;
    typedef QHash<QString, QString> dtkAbstractProcessInterfacesHash;

public:
    static dtkAbstractProcessFactory *instance(void);

    bool registerProcessType(const QString& type, dtkAbstractProcessCreator func);
    bool registerProcessType(const QString& type, dtkAbstractProcessCreator func, const QString& interface);

    unsigned int size(const QString& type);

    dtkAbstractProcess *get(const QString& type, int index = 0);
    dtkAbstractProcess *get(const QString& type, const QString& name);

    bool exists(const QString& type);

    QStringList creators(void) const;
    QStringList implementations(const QString& abstraction);

signals:
    void created(dtkAbstractProcess *process, const QString& type);

public slots:
    dtkAbstractProcess *create(const QString& type);

protected:
     dtkAbstractProcessFactory(void);
    ~dtkAbstractProcessFactory(void);

private:
    static dtkAbstractProcessFactory   *s_instance;

private:
    dtkAbstractProcessFactoryPrivate *d;
};

#endif
