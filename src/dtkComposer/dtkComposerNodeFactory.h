/* dtkComposerNodeFactory.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb  7 22:27:06 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  7 23:08:05 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEFACTORY_H
#define DTKCOMPOSERNODEFACTORY_H

#include <QtCore>

class dtkComposerNode;
class dtkComposerNodeFactoryPrivate;

class dtkComposerNodeFactory : public QObject
{
    Q_OBJECT

public:
    static dtkComposerNodeFactory *instance(void);

public slots:
    dtkComposerNode *create(QString type);

protected:
     dtkComposerNodeFactory(void);
    ~dtkComposerNodeFactory(void);

protected:
    static dtkComposerNodeFactory *s_instance;

private:
    dtkComposerNodeFactoryPrivate *d;
};

#endif
