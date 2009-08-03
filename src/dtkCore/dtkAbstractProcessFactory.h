/* dtkAbstractProcessFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr  7 10:37:19 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 37
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

class DTKCORE_EXPORT dtkAbstractProcessFactory : public dtkAbstractFactory
{
    Q_OBJECT

public:
    typedef dtkAbstractProcess *(*dtkAbstractProcessCreator)(void);
    typedef QMap<QString, dtkAbstractProcessCreator> dtkAbstractProcessCreatorMap;

public:
    static dtkAbstractProcessFactory *instance(void);

    bool registerProcessType(QString type, dtkAbstractProcessCreator func);

public slots:
    dtkAbstractProcess *create(QString type);

protected:
    dtkAbstractProcessFactory(void);

private:
    dtkAbstractProcessCreatorMap m_creators;
    
    static dtkAbstractProcessFactory   *m_instance;
};

#endif
