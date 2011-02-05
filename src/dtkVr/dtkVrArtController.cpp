/* dtkVrArtController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb  4 18:12:09 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  4 18:27:46 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 50
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrArtController_p.h"
#include "dtkVrArtController.h"

#include <QtDebug>

// /////////////////////////////////////////////////////////////////
// dtkVrArtController
// /////////////////////////////////////////////////////////////////

dtkVrArtController::dtkVrArtController(void) : QObject(), d(new dtkVrArtControllerPrivate)
{
    d->tracker = NULL;
}

dtkVrArtController::~dtkVrArtController(void)
{
    delete d;

    d = NULL;
}

void dtkVrArtController::setServer(const QString& server)
{
    d->url = server;
}

void dtkVrArtController::start(void)
{
    if (d->tracker)
        delete d->tracker;

    d->tracker = new DTrack2(d->url.toAscii().constData());

    if(!d->tracker->valid())
        qDebug() << "DTrack initialization error";
    else
        qDebug() << "Connected to" << d->url << "om port" << d->tracker->get_data_port();    
}

void dtkVrArtController::stop(void)
{
    if (d->tracker)
        delete d->tracker;

    qDebug() << "Connection to" << d->url << "succesfully closed";
}
