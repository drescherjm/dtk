/* dtkLogDestination.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 15:15:19 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar  5 12:28:40 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 59
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkLogDestination.h"
#include "dtkLogModel.h"

// /////////////////////////////////////////////////////////////////
// dtkLogDestination
// /////////////////////////////////////////////////////////////////

dtkLogDestination::~dtkLogDestination(void)
{

}

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationConsole
// /////////////////////////////////////////////////////////////////

void dtkLogDestinationConsole::write(const QString& message)
{
    fprintf(stderr, "%s\n", qPrintable(message));
    fflush(stderr);
}

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationFile
// /////////////////////////////////////////////////////////////////

class dtkLogDestinationFilePrivate
{
public:
    QFile file;

public:
    QTextStream stream;
};

dtkLogDestinationFile::dtkLogDestinationFile(const QString& path) : d(new dtkLogDestinationFilePrivate)
{
    d->file.setFileName(path);
    d->file.open(QFile::WriteOnly | QFile::Text | QIODevice::Append);

    d->stream.setDevice(&(d->file));
}

dtkLogDestinationFile::~dtkLogDestinationFile(void)
{
    delete d;

    d = NULL;
}

void dtkLogDestinationFile::write(const QString& message)
{
    d->stream << message << endl;
    d->stream.flush();
}

// /////////////////////////////////////////////////////////////////
// dtkLogDestinationModel
// /////////////////////////////////////////////////////////////////

class dtkLogDestinationModelPrivate
{
public:
    dtkLogModel *model;
};

dtkLogDestinationModel::dtkLogDestinationModel(dtkLogModel *model) : d(new dtkLogDestinationModelPrivate)
{
    d->model = model;
}

dtkLogDestinationModel::~dtkLogDestinationModel(void)
{
    delete d;

    d = NULL;
}

void dtkLogDestinationModel::write(const QString& message)
{
    d->model->append(message);
}
