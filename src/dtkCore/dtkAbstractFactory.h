/* dtkAbstractFactory.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 12 11:03:31 2008 (+0100)
 * Version: $Id$
 * Last-Updated:  Wed Mar 25 13:48:43 2009
 *           By: Jean-Christophe Lombardo
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTFACTORY_H
#define DTKABSTRACTFACTORY_H

#include <QtCore/QObject>

#include <dtkCore/dtkCoreExport.h>
#include <dtkCore/dtkGlobal.h>

class DTKCORE_EXPORT dtkAbstractFactory : public QObject
{
    Q_OBJECT
public:
     dtkAbstractFactory(void);
    ~dtkAbstractFactory(void);

private slots:
    void clear(void) {/*printf("Clearing a factory\n");*/ delete this;}
};

#endif
