/* dtkAbstractProcessFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Sep 17 16:55:42 2010 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 59
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

    bool registerProcessType(QString type, dtkAbstractProcessCreator func);
    bool registerProcessType(QString type, dtkAbstractProcessCreator func, QString interface);

    unsigned int size(QString type);

    dtkAbstractProcess *get(QString type, int index = 0);
    dtkAbstractProcess *get(QString type, QString name);

    bool exists(QString type);

    QStringList implementations(const QString& abstraction);

signals:
    void created(dtkAbstractProcess *process, QString type);

public slots:
    dtkAbstractProcess *create(QString type);

protected:
     dtkAbstractProcessFactory(void);
    ~dtkAbstractProcessFactory(void);

private:
    static dtkAbstractProcessFactory   *s_instance;

private:
    dtkAbstractProcessFactoryPrivate *d;
};

#endif
