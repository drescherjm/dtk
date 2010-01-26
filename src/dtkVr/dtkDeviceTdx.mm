/* dtkDeviceTdx.mm --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Jan 24 21:30:13 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 26 21:09:37 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 43
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDeviceTdx.h"

#include <3DconnexionClient/ConnexionClientAPI.h>

// /////////////////////////////////////////////////////////////////
// dtkDeviceTdxPrivate
// /////////////////////////////////////////////////////////////////

class dtkDeviceTdxPrivate
{
public:
    static void handler(io_connect_t connection, natural_t type, void *argument);

    static dtkDeviceTdxPrivate *self;
    
public:
    UInt16 id;

public:
    dtkDeviceTdx *q;
};

void dtkDeviceTdxPrivate::handler(io_connect_t connection, natural_t type, void *argument)
{
    Q_UNUSED(connection);

    ConnexionDeviceState *state;
    
    switch(type) {

    case kConnexionMsgDeviceState:
	state = (ConnexionDeviceState *)argument;

	if(state->client == self->id) switch(state->command) {
	    case kConnexionCmdHandleAxis:
                self->q->runHandlers(state->axis[0], state->axis[1], state->axis[2], state->axis[3], state->axis[4], state->axis[5]);
		break;
	    case kConnexionCmdHandleButtons:
		if(state->buttons & kConnexionMaskButton1)
                    emit self->q->buttonPressed(dtkDeviceTdx::dtkDeviceTdxButtonOne);
		if(state->buttons & kConnexionMaskButton2)
                    emit self->q->buttonPressed(dtkDeviceTdx::dtkDeviceTdxButtonTwo);
		break;
	    default:
		break;
	}
	break;

    default:
	break;
    }
}

dtkDeviceTdxPrivate *dtkDeviceTdxPrivate::self = NULL;

// /////////////////////////////////////////////////////////////////
// dtkDeviceTdx
// /////////////////////////////////////////////////////////////////

dtkDeviceTdx::dtkDeviceTdx(void) : dtkAbstractDevice(), d(new dtkDeviceTdxPrivate)
{
    d->self = d;
    d->q = this;
}

dtkDeviceTdx::~dtkDeviceTdx(void)
{
    this->stopConnection();

    delete d;

    d = NULL;
}

void dtkDeviceTdx::registerHandler(dtkDeviceTdx::dtkDeviceTdxHandler handler)
{
    this->handlers << handler;
}

QString dtkDeviceTdx::description(void) const
{
    return "dtkDeviceTdx";
}

void dtkDeviceTdx::startConnection(void)
{
    if(InstallConnexionHandlers == NULL) {
        qDebug() << "3Dconnexion framework not found!";
        return;
    }

    if(InstallConnexionHandlers(dtkDeviceTdxPrivate::handler, 0l, 0l)) {
	qDebug() << "Unable to install handler for Tdx device.";
	return;
    }

    d->id = RegisterConnexionClient(kConnexionClientWildcard, 0L, kConnexionClientModeTakeOver, kConnexionMaskAll);

    if(!d->id) {
	qDebug() << "3Dconnexion device initialization failed.";
	return;
    } else
	qDebug() << "3Dconnexion device initialized. Client ID:" << d->id;

}

void dtkDeviceTdx::stopConnection(void)
{
    if (InstallConnexionHandlers == NULL)
        return;
    
    if (d->id) {
        UnregisterConnexionClient(d->id);
	CleanupConnexionHandlers();
	qDebug() << "Terminated connection with 3Dconnexion device.";
    }
}

void dtkDeviceTdx::runHandlers(float tx, float ty, float tz, float rx, float ry, float rz)
{
    foreach(dtkDeviceTdx::dtkDeviceTdxHandler handler, this->handlers)
        (handler)(tx, ty, tz, rx, ry, rz);
}
