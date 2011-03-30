/* dtkComposerNodeFactory.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb  7 22:27:06 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 25 10:13:39 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEFACTORY_H
#define DTKCOMPOSERNODEFACTORY_H

#include "dtkComposerExport.h"

#include <QtCore>

class dtkComposerNode;
class dtkComposerNodeFactoryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeFactory : public QObject
{
    Q_OBJECT

public:
     dtkComposerNodeFactory(void);
    ~dtkComposerNodeFactory(void);

public slots:
    virtual dtkComposerNode *create(QString type);

private:
    dtkComposerNodeFactoryPrivate *d;
};

#endif
