/* dtkComposerNodeFactory.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb  7 22:27:06 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Oct 18 10:27:24 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
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
    virtual ~dtkComposerNodeFactory(void);

public slots:
    virtual dtkComposerNode *create(QString type);

private:
    dtkComposerNodeFactoryPrivate *d;
};

#endif
