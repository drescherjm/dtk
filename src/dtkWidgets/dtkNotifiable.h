/* dtkNotifiable.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Apr 23 11:49:55 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:53:58 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 17
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKNOTIFIABLE_H
#define DTKNOTIFIABLE_H

#include "dtkWidgetsExport.h"

#include <QtCore>

class DTKWIDGETS_EXPORT dtkNotifiable
{
public:
    virtual void clear(void) = 0;

public:
    virtual void next(void) = 0;
    virtual void previous(void) = 0;

public:
    virtual void dismiss(void) = 0;
    virtual void dismissible(bool dismissible) = 0;

public:
    virtual void setPersistentCount(int count) = 0;
    virtual void setNonPersistentCount(int count) = 0;

public:
    virtual void display(const QString& message) = 0;
};

#endif
