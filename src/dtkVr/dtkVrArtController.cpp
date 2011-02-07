/* dtkVrArtController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb  4 18:12:09 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb  5 02:18:06 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 58
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

    if(!d->tracker->send_command("init"))
        qDebug() << "DTrack initialization error";
    else
        qDebug() << "DTrack initialization success";

    if(!d->tracker->send_command("tracking start"))
        qDebug() << "DTrack start failed";
    else
        qDebug() << "DTrack start success";
}

void dtkVrArtController::stop(void)
{
    if (d->tracker) {
        delete d->tracker;
        d->tracker = NULL;
    }

    qDebug() << "Connection to" << d->url << "succesfully closed";
}
