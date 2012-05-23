/* dtkAbstractProcessFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jul  5 15:22:37 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 64
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

#include "dtkAbstractFactory.h"

                  class dtkAbstractProcess;
                  class dtkAbstractProcessFactoryPrivate;
template<class T> class dtkSmartPointer;

class DTKCORE_EXPORT dtkAbstractProcessFactory : public dtkAbstractFactory
{
    Q_OBJECT

public:
    typedef dtkAbstractProcess *(*dtkAbstractProcessCreator)(void);

public:
    static dtkAbstractProcessFactory *instance(void);

    bool registerProcessType(const QString& type, dtkAbstractProcessCreator func);
    bool registerProcessType(const QString& type, dtkAbstractProcessCreator func, const QString& interface);

    unsigned int size(const QString& type);

    bool exists(const QString& type);

    QStringList creators(void) const;

    QStringList implementations(const QString& interface);
    QStringList interfaces(void);

    dtkSmartPointer<dtkAbstractProcess> createSmartPointer(const QString& type);

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
