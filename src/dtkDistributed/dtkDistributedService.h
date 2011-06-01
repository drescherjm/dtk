/* dtkDistributedService.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu May 26 09:43:06 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 10:32:43 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVICE_H
#define DTKDISTRIBUTEDSERVICE_H

#include "dtkDistributedExport.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkDistributedServiceController
// /////////////////////////////////////////////////////////////////

class dtkDistributedServiceControllerPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedServiceController
{
    Q_DECLARE_PRIVATE(dtkDistributedServiceController)

public:
    enum StartupType
    {
          AutoStartup = 0,
        ManualStartup
    };

             dtkDistributedServiceController(const QString &name);
    virtual ~dtkDistributedServiceController(void);

    bool isInstalled(void) const;
    bool isRunning(void) const;

    QString serviceName(void) const;
    QString serviceDescription(void) const;
    StartupType startupType(void) const;
    QString serviceFilePath(void) const;

    static bool   install(const QString &serviceFilePath, const QString &account = QString(), const QString &password = QString());
           bool uninstall(void);

    bool start(const QStringList &arguments);
    bool start(void);
    bool stop(void);
    bool pause(void);
    bool resume(void);
    bool sendCommand(int code);

private:
    dtkDistributedServiceControllerPrivate *d_ptr;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedServiceBase
// /////////////////////////////////////////////////////////////////

class dtkDistributedServiceBasePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedServiceBase
{
    Q_DECLARE_PRIVATE(dtkDistributedServiceBase)

public:
    enum MessageType
    {
	    Success = 0,
              Error,
            Warning,
        Information
    };

    enum ServiceFlag
    {
                    Default = 0x00,
             CanBeSuspended = 0x01,
            CannotBeStopped = 0x02,
        NeedsStopOnShutdown = 0x04
    };

    Q_DECLARE_FLAGS(ServiceFlags, ServiceFlag)

             dtkDistributedServiceBase(int argc, char **argv, const QString &name);
    virtual ~dtkDistributedServiceBase();

    QString serviceName(void) const;

    QString serviceDescription(void) const;
    void setServiceDescription(const QString &description);

    dtkDistributedServiceController::StartupType startupType(void) const;
    void setStartupType(dtkDistributedServiceController::StartupType startupType);

    ServiceFlags serviceFlags(void) const;
    void setServiceFlags(ServiceFlags flags);

    int exec(void);

    void logMessage(const QString &message, MessageType type = Success, int id = 0, uint category = 0, const QByteArray &data = QByteArray());

    static dtkDistributedServiceBase *instance();

protected:
    virtual void start(void) = 0;
    virtual void stop(void);
    virtual void pause(void);
    virtual void resume(void);
    virtual void processCommand(int code);

    virtual void createApplication(int &argc, char **argv) = 0;
    virtual int executeApplication(void) = 0;

private:
    friend class dtkDistributedServiceSysPrivate; dtkDistributedServiceBasePrivate *d_ptr;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template <typename Application> class dtkDistributedService : public dtkDistributedServiceBase
{
public:
     dtkDistributedService(int argc, char **argv, const QString &name) : dtkDistributedServiceBase(argc, argv, name), app(0) {}
    ~dtkDistributedService(void) {}

protected:
    Application *application(void) const
    {
        return app;
    }

    virtual void createApplication(int &argc, char **argv)
    {
        app = new Application(argc, argv);
        QCoreApplication *a = app;
        Q_UNUSED(a);
    }

    virtual int executeApplication(void) {
        return Application::exec();
    }

private:
    Application *app;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributedServiceBase::ServiceFlags)

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
*******************************************************************/
