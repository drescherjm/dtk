/* dtkCoreApplication.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/04 12:03:44
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkCoreApplication.h"
#include "dtkApplicationPrivate.h"

dtkCoreApplication::dtkCoreApplication(int &argc, char **argv): QCoreApplication(argc, argv)
{
    d = new dtkApplicationPrivate;
    d->setApplication(this);
}

dtkCoreApplication::~dtkCoreApplication(void)
{
    delete d;
    d = NULL;
}

QSettings *dtkCoreApplication::settings(void)
{
    return d->settings;
}

QCommandLineParser *dtkCoreApplication::parser(void)
{
    return d->parser;
}

void dtkCoreApplication::initialize(void)
{
    d->initialize();
}
