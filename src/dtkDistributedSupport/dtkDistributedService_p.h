/* dtkDistributedService_p.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu May 26 10:31:56 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 10:34:46 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKDISTRIBUTEDSERVICE_P_H
#define DTKDISTRIBUTEDSERVICE_P_H

#include "dtkDistributedService.h"

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkDistributedServiceControllerPrivate
{
    Q_DECLARE_PUBLIC(dtkDistributedServiceController)

public:
    QString serviceName;
    dtkDistributedServiceController *q_ptr;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkDistributedServiceBasePrivate
{
    Q_DECLARE_PUBLIC(dtkDistributedServiceBase)

public:
    dtkDistributedServiceBasePrivate(const QString& name);
    ~dtkDistributedServiceBasePrivate(void);

    dtkDistributedServiceBase *q_ptr;

    QString serviceDescription;
    dtkDistributedServiceController::StartupType startupType;
    dtkDistributedServiceBase::ServiceFlags serviceFlags;
    QStringList args;

    static class dtkDistributedServiceBase *instance;

    dtkDistributedServiceController controller;

    void startService(void);
    int run(bool asService, const QStringList& argList);
    bool install(const QString& account, const QString& password);

    bool start(void);

    QString filePath(void) const;
    bool sysInit(void);
    void sysSetPath(void);
    void sysCleanup(void);

    class dtkDistributedServiceSysPrivate *sysd;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkDistributedServiceStarter : public QObject
{
    Q_OBJECT

public:
    dtkDistributedServiceStarter(dtkDistributedServiceBasePrivate *service) : QObject(), d_ptr(service) {}

public slots:
    void slotStart(void) {
        d_ptr->startService();
    }

private:
    dtkDistributedServiceBasePrivate *d_ptr;
};

#endif

// /////////////////////////////////////////////////////////////////
// Credits
// /////////////////////////////////////////////////////////////////

/*******************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of a Qt Solutions component.
**
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
*********************************************************************/
