/* dtkLogDestination.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 15:10:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  1 18:01:37 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKLOGDESTINATION_H
#define DTKLOGDESTINATION_H

#include "dtkLogExport.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkLogDestination
// /////////////////////////////////////////////////////////////////

class DTKLOG_EXPORT dtkLogDestination
{
public:
    virtual ~dtkLogDestination(void);

public:
    virtual void write(const QString& message) = 0;
};

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationConsole
// /////////////////////////////////////////////////////////////////

class DTKLOG_EXPORT dtkLogDestinationConsole : public dtkLogDestination
{
public:
    void write(const QString& message);
};

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationFile
// /////////////////////////////////////////////////////////////////

class dtkLogDestinationFilePrivate;

class DTKLOG_EXPORT dtkLogDestinationFile : public dtkLogDestination
{
public:
     dtkLogDestinationFile(const QString& path);
    ~dtkLogDestinationFile(void);

public:
    void write(const QString& message);

private:
    dtkLogDestinationFilePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationPointer
// /////////////////////////////////////////////////////////////////

typedef QSharedPointer<dtkLogDestination> dtkLogDestinationPointer;

#endif
