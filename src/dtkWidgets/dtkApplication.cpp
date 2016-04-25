/* dtkApplication.cpp ---
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

#include "dtkApplication.h"
#include <dtkCore/dtkApplicationPrivate.h>

dtkApplication::dtkApplication(int &argc, char **argv): QApplication(argc, argv)
{
    d = new dtkApplicationPrivate;
    d->setApplication(this);
}

dtkApplication::~dtkApplication(void)
{
    delete d;
    d = NULL;
}

QSettings *dtkApplication::settings(void)
{
    return d->settings;
}

bool dtkApplication::noGui(void)
{
    return !(qApp && qobject_cast<QGuiApplication *>(qApp) && (QGuiApplication::platformName() != "minimal")) ;
}

QCommandLineParser *dtkApplication::parser(void)
{
    return d->parser;
}

void dtkApplication::initialize(void)
{
    d->initialize();
}

