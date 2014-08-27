/* dtkDistributedServiceWin.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu May 26 10:40:36 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 10:52:08 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 36
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedService.h"
#include "dtkDistributedService_p.h"
#include "dtkDistributedServiceWin_p.h"

#include <QtCore>
#include <QtDebug>

#include <qt_windows.h>

#include <stdio.h>

#ifndef MAX_PATH
#define	MAX_PATH	(260)
#endif

#define	_MAX_PATH	MAX_PATH

typedef SERVICE_STATUS_HANDLE(WINAPI*PRegisterServiceCtrlHandler)(const wchar_t*,LPHANDLER_FUNCTION);
static PRegisterServiceCtrlHandler pRegisterServiceCtrlHandler = 0;
typedef BOOL(WINAPI*PSetServiceStatus)(SERVICE_STATUS_HANDLE,LPSERVICE_STATUS);
static PSetServiceStatus pSetServiceStatus = 0;
typedef BOOL(WINAPI*PChangeServiceConfig2)(SC_HANDLE,DWORD,LPVOID);
static PChangeServiceConfig2 pChangeServiceConfig2 = 0;
typedef BOOL(WINAPI*PCloseServiceHandle)(SC_HANDLE);
static PCloseServiceHandle pCloseServiceHandle = 0;
typedef SC_HANDLE(WINAPI*PCreateService)(SC_HANDLE,LPCTSTR,LPCTSTR,DWORD,DWORD,DWORD,DWORD,LPCTSTR,LPCTSTR,LPDWORD,LPCTSTR,LPCTSTR,LPCTSTR);
static PCreateService pCreateService = 0;
typedef SC_HANDLE(WINAPI*POpenSCManager)(LPCTSTR,LPCTSTR,DWORD);
static POpenSCManager pOpenSCManager = 0;
typedef BOOL(WINAPI*PDeleteService)(SC_HANDLE);
static PDeleteService pDeleteService = 0;
typedef SC_HANDLE(WINAPI*POpenService)(SC_HANDLE,LPCTSTR,DWORD);
static POpenService pOpenService = 0;
typedef BOOL(WINAPI*PQueryServiceStatus)(SC_HANDLE,LPSERVICE_STATUS);
static PQueryServiceStatus pQueryServiceStatus = 0;
typedef BOOL(WINAPI*PStartServiceCtrlDispatcher)(CONST SERVICE_TABLE_ENTRY*);
static PStartServiceCtrlDispatcher pStartServiceCtrlDispatcher = 0;
typedef BOOL(WINAPI*PStartService)(SC_HANDLE,DWORD,const wchar_t**);
static PStartService pStartService = 0;
typedef BOOL(WINAPI*PControlService)(SC_HANDLE,DWORD,LPSERVICE_STATUS);
static PControlService pControlService = 0;
typedef HANDLE(WINAPI*PDeregisterEventSource)(HANDLE);
static PDeregisterEventSource pDeregisterEventSource = 0;
typedef BOOL(WINAPI*PReportEvent)(HANDLE,WORD,WORD,DWORD,PSID,WORD,DWORD,LPCTSTR*,LPVOID);
static PReportEvent pReportEvent = 0;
typedef HANDLE(WINAPI*PRegisterEventSource)(LPCTSTR,LPCTSTR);
static PRegisterEventSource pRegisterEventSource = 0;
typedef DWORD(WINAPI*PRegisterServiceProcess)(DWORD,DWORD);
static PRegisterServiceProcess pRegisterServiceProcess = 0;
typedef BOOL(WINAPI*PQueryServiceConfig)(SC_HANDLE,LPQUERY_SERVICE_CONFIG,DWORD,LPDWORD);
static PQueryServiceConfig pQueryServiceConfig = 0;
typedef BOOL(WINAPI*PQueryServiceConfig2)(SC_HANDLE,DWORD,LPBYTE,DWORD,LPDWORD);
static PQueryServiceConfig2 pQueryServiceConfig2 = 0;

#define RESOLVE(name) p##name = (P##name)lib.resolve(#name);
#define RESOLVEA(name) p##name = (P##name)lib.resolve(#name"A");
#define RESOLVEW(name) p##name = (P##name)lib.resolve(#name"W");

static bool winServiceInit(void)
{
    if (!pOpenSCManager) {
        QLibrary lib("advapi32");

        // only resolve unicode versions
        RESOLVEW(RegisterServiceCtrlHandler);
        RESOLVE(SetServiceStatus);
        RESOLVEW(ChangeServiceConfig2);
        RESOLVE(CloseServiceHandle);
        RESOLVEW(CreateService);
        RESOLVEW(OpenSCManager);
        RESOLVE(DeleteService);
        RESOLVEW(OpenService);
        RESOLVE(QueryServiceStatus);
        RESOLVEW(StartServiceCtrlDispatcher);
        RESOLVEW(StartService); // need only Ansi version
        RESOLVE(ControlService);
        RESOLVE(DeregisterEventSource);
        RESOLVEW(ReportEvent);
        RESOLVEW(RegisterEventSource);
        RESOLVEW(QueryServiceConfig);
        RESOLVEW(QueryServiceConfig2);
    }
    return pOpenSCManager != 0;
}

bool dtkDistributedServiceController::isInstalled(void) const
{
    Q_D(const dtkDistributedServiceController);
    bool result = false;
    if (!winServiceInit())
        return result;

    // Open the Service Control Manager
    SC_HANDLE hSCM = pOpenSCManager(0, 0, 0);
    if (hSCM) {
        // Try to open the service
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(),
                                          SERVICE_QUERY_CONFIG);

        if (hService) {
            result = true;
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

bool dtkDistributedServiceController::isRunning(void) const
{
    Q_D(const dtkDistributedServiceController);
    bool result = false;
    if (!winServiceInit())
        return result;

    // Open the Service Control Manager
    SC_HANDLE hSCM = pOpenSCManager(0, 0, 0);
    if (hSCM) {
        // Try to open the service
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(),
                                          SERVICE_QUERY_STATUS);
        if (hService) {
            SERVICE_STATUS info;
            int res = pQueryServiceStatus(hService, &info);
            if (res)
                result = info.dwCurrentState != SERVICE_STOPPED;
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

QString dtkDistributedServiceController::serviceFilePath(void) const
{
    Q_D(const dtkDistributedServiceController);
    QString result;
    if (!winServiceInit())
        return result;

    // Open the Service Control Manager
    SC_HANDLE hSCM = pOpenSCManager(0, 0, 0);
    if (hSCM) {
        // Try to open the service
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(),
                                          SERVICE_QUERY_CONFIG);
        if (hService) {
            DWORD sizeNeeded = 0;
            char data[8 * 1024];
            if (pQueryServiceConfig(hService, (LPQUERY_SERVICE_CONFIG)data, 8 * 1024, &sizeNeeded)) {
                LPQUERY_SERVICE_CONFIG config = (LPQUERY_SERVICE_CONFIG)data;
                result = QString::fromUtf16((const ushort*)config->lpBinaryPathName);
            }
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

QString dtkDistributedServiceController::serviceDescription(void) const
{
    Q_D(const dtkDistributedServiceController);
    QString result;
    if (!winServiceInit())
        return result;

    // Open the Service Control Manager
    SC_HANDLE hSCM = pOpenSCManager(0, 0, 0);
    if (hSCM) {
        // Try to open the service
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(),
             SERVICE_QUERY_CONFIG);
        if (hService) {
            DWORD dwBytesNeeded;
            char data[8 * 1024];
            if (pQueryServiceConfig2(
                    hService,
                    SERVICE_CONFIG_DESCRIPTION,
                    (unsigned char *)data,
                    8096,
                    &dwBytesNeeded)) {
                LPSERVICE_DESCRIPTION desc = (LPSERVICE_DESCRIPTION)data;
                if (desc->lpDescription)
                    result = QString::fromUtf16((const ushort*)desc->lpDescription);
            }
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

dtkDistributedServiceController::StartupType dtkDistributedServiceController::startupType(void) const
{
    Q_D(const dtkDistributedServiceController);
    StartupType result = ManualStartup;
    if (!winServiceInit())
        return result;

    // Open the Service Control Manager
    SC_HANDLE hSCM = pOpenSCManager(0, 0, 0);
    if (hSCM) {
        // Try to open the service
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(),
                                          SERVICE_QUERY_CONFIG);
        if (hService) {
            DWORD sizeNeeded = 0;
            char data[8 * 1024];
            if (pQueryServiceConfig(hService, (QUERY_SERVICE_CONFIG *)data, 8 * 1024, &sizeNeeded)) {
                QUERY_SERVICE_CONFIG *config = (QUERY_SERVICE_CONFIG *)data;
                result = config->dwStartType == SERVICE_DEMAND_START ? ManualStartup : AutoStartup;
            }
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

bool dtkDistributedServiceController::uninstall(void)
{
    Q_D(dtkDistributedServiceController);
    bool result = false;
    if (!winServiceInit())
        return result;

    // Open the Service Control Manager
    SC_HANDLE hSCM = pOpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
    if (hSCM) {
        // Try to open the service
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(), DELETE);
        if (hService) {
            if (pDeleteService(hService))
                result = true;
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

bool dtkDistributedServiceController::start(const QStringList &args)
{
    Q_D(dtkDistributedServiceController);
    bool result = false;
    if (!winServiceInit())
        return result;

    // Open the Service Control Manager
    SC_HANDLE hSCM = pOpenSCManager(0, 0, SC_MANAGER_CONNECT);
    if (hSCM) {
        // Try to open the service
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(), SERVICE_START);
        if (hService) {
            QVector<const wchar_t *> argv(args.size());
            for (int i = 0; i < args.size(); ++i)
                argv[i] = (const wchar_t*)args.at(i).utf16();

            if (pStartService(hService, args.size(), argv.data()))
                result = true;
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

bool dtkDistributedServiceController::stop(void)
{
    Q_D(dtkDistributedServiceController);
    bool result = false;
    if (!winServiceInit())
        return result;

    SC_HANDLE hSCM = pOpenSCManager(0, 0, SC_MANAGER_CONNECT);
    if (hSCM) {
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(), SERVICE_STOP|SERVICE_QUERY_STATUS);
        if (hService) {
            SERVICE_STATUS status;
            if (pControlService(hService, SERVICE_CONTROL_STOP, &status)) {
                bool stopped = status.dwCurrentState == SERVICE_STOPPED;
                int i = 0;
                while(!stopped && i < 10) {
                    Sleep(200);
                    if (!pQueryServiceStatus(hService, &status))
                        break;
                    stopped = status.dwCurrentState == SERVICE_STOPPED;
                    ++i;
                }
                result = stopped;
            } else {
                qErrnoWarning(GetLastError(), "stopping");
            }
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

bool dtkDistributedServiceController::pause(void)
{
    Q_D(dtkDistributedServiceController);
    bool result = false;
    if (!winServiceInit())
        return result;

    SC_HANDLE hSCM = pOpenSCManager(0, 0, SC_MANAGER_CONNECT);
    if (hSCM) {
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(),
                             SERVICE_PAUSE_CONTINUE);
        if (hService) {
            SERVICE_STATUS status;
            if (pControlService(hService, SERVICE_CONTROL_PAUSE, &status))
                result = true;
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

bool dtkDistributedServiceController::resume(void)
{
    Q_D(dtkDistributedServiceController);
    bool result = false;
    if (!winServiceInit())
        return result;

    SC_HANDLE hSCM = pOpenSCManager(0, 0, SC_MANAGER_CONNECT);
    if (hSCM) {
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(),
                             SERVICE_PAUSE_CONTINUE);
        if (hService) {
            SERVICE_STATUS status;
            if (pControlService(hService, SERVICE_CONTROL_CONTINUE, &status))
                result = true;
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

bool dtkDistributedServiceController::sendCommand(int code)
{
   Q_D(dtkDistributedServiceController);
   bool result = false;
   if (!winServiceInit())
        return result;

    if (code < 0 || code > 127 || !isRunning())
        return result;

    SC_HANDLE hSCM = pOpenSCManager(0, 0, SC_MANAGER_CONNECT);
    if (hSCM) {
        SC_HANDLE hService = pOpenService(hSCM, (LPCTSTR)d->serviceName.utf16(),
                                          SERVICE_USER_DEFINED_CONTROL);
        if (hService) {
            SERVICE_STATUS status;
            if (pControlService(hService, 128 + code, &status))
                result = true;
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

#if defined(QTSERVICE_DEBUG)
extern void qtServiceLogDebug(dtkDistributedMsgType type, const char* msg);
#endif

void dtkDistributedServiceBase::logMessage(const QString &message, MessageType type, int id, uint category, const QByteArray &data)
{
#if defined(QTSERVICE_DEBUG)
    QByteArray dbgMsg("[LOGGED ");
    switch (type) {
    case Error: dbgMsg += "Error] " ; break;
    case Warning: dbgMsg += "Warning] "; break;
    case Success: dbgMsg += "Success] "; break;
    case Information: //fall through
    default: dbgMsg += "Information] "; break;
    }
    dbgMsg += message.toUtf8();
    qtServiceLogDebug((dtkDistributedMsgType)-1, dbgMsg.constData());
#endif

    Q_D(dtkDistributedServiceBase);
    if (!winServiceInit())
        return;
    WORD wType;
    switch (type) {
    case Error: wType = EVENTLOG_ERROR_TYPE; break;
    case Warning: wType = EVENTLOG_WARNING_TYPE; break;
    case Information: wType = EVENTLOG_INFORMATION_TYPE; break;
    default: wType = EVENTLOG_SUCCESS; break;
    }
    HANDLE h = pRegisterEventSource(0, (LPCSTR)d->controller.serviceName().utf16());
    if (h) {
        const wchar_t *msg = (wchar_t*)message.utf16();
        const char *bindata = data.size() ? data.constData() : 0;
        pReportEvent(h, wType, category, id, 0, 1, data.size(),(LPCTSTR*)&msg,
                     const_cast<char *>(bindata));
        pDeregisterEventSource(h);
    }
}

#include "dtkDistributedServiceWin_p.h"

class dtkDistributedServiceSysPrivate
{
public:
    enum {
        QTSERVICE_STARTUP = 256
    };
    dtkDistributedServiceSysPrivate();

    void setStatus( DWORD dwState );
    void setServiceFlags(dtkDistributedServiceBase::ServiceFlags flags);
    DWORD serviceFlags(dtkDistributedServiceBase::ServiceFlags flags) const;
    inline bool available() const;
    static void WINAPI serviceMain( DWORD dwArgc, wchar_t** lpszArgv );
    static void WINAPI handler( DWORD dwOpcode );

    SERVICE_STATUS status;
    SERVICE_STATUS_HANDLE serviceStatus;
    QStringList serviceArgs;

    static dtkDistributedServiceSysPrivate *instance;

    static EventFilter nextFilter;

    QWaitCondition condition;
    QMutex mutex;
    QSemaphore startSemaphore;
    QSemaphore startSemaphore2;

    dtkDistributedServiceControllerHandler *controllerHandler;

    void handleCustomEvent(QEvent *e);
};

dtkDistributedServiceControllerHandler::dtkDistributedServiceControllerHandler(dtkDistributedServiceSysPrivate *sys) : QObject(), d_sys(sys)
{

}

void dtkDistributedServiceControllerHandler::customEvent(QEvent *e)
{
    d_sys->handleCustomEvent(e);
}

dtkDistributedServiceSysPrivate *dtkDistributedServiceSysPrivate::instance = 0;

EventFilter dtkDistributedServiceSysPrivate::nextFilter = 0;

dtkDistributedServiceSysPrivate::dtkDistributedServiceSysPrivate(void)
{
    instance = this;
}

inline bool dtkDistributedServiceSysPrivate::available(void) const
{
    return 0 != pOpenSCManager;
}

void WINAPI dtkDistributedServiceSysPrivate::serviceMain(DWORD dwArgc, wchar_t** lpszArgv)
{
    if (!instance || !dtkDistributedServiceBase::instance())
        return;

    // Windows spins off a random thread to call this function on
    // startup, so here we just signal to the QApplication event loop
    // in the main thread to go ahead with start()'ing the service.

    for (DWORD i = 0; i < dwArgc; i++)
        instance->serviceArgs.append(QString::fromUtf16((unsigned short*)lpszArgv[i]));

    instance->startSemaphore.release(); // let the qapp creation start
    instance->startSemaphore2.acquire(); // wait until its done
    // Register the control request handler
    instance->serviceStatus = pRegisterServiceCtrlHandler((const wchar_t *)dtkDistributedServiceBase::instance()->serviceName().utf16(), handler);

    if (!instance->serviceStatus) // cannot happen - something is utterly wrong
        return;

    handler(QTSERVICE_STARTUP); // Signal startup to the application -
                                // causes dtkDistributedServiceBase::start() to be called in the main thread

    // The MSDN doc says that this thread should just exit - the service is
    // running in the main thread (here, via callbacks in the handler thread).
}

// The handler() is called from the thread that called
// StartServiceCtrlDispatcher, i.e. our HandlerThread, and
// not from the main thread that runs the event loop, so we
// have to post an event to ourselves, and use a QWaitCondition
// and a QMutex to synchronize.

void dtkDistributedServiceSysPrivate::handleCustomEvent(QEvent *e)
{
    int code = e->type() - QEvent::User;

    switch(code) {
    case QTSERVICE_STARTUP: // Startup
        dtkDistributedServiceBase::instance()->start();
        break;
    case SERVICE_CONTROL_STOP:
        dtkDistributedServiceBase::instance()->stop();
        QCoreApplication::instance()->quit();
        break;
    case SERVICE_CONTROL_PAUSE:
        dtkDistributedServiceBase::instance()->pause();
        break;
    case SERVICE_CONTROL_CONTINUE:
        dtkDistributedServiceBase::instance()->resume();
        break;
    default:
	if (code >= 128 && code <= 255)
	    dtkDistributedServiceBase::instance()->processCommand(code - 128);
        break;
    }

    mutex.lock();
    condition.wakeAll();
    mutex.unlock();
}

void WINAPI dtkDistributedServiceSysPrivate::handler(DWORD code)
{
    if (!instance)
        return;

    instance->mutex.lock();
    switch (code) {
    case QTSERVICE_STARTUP: // dtkDistributedService startup (called from WinMain when started)
        instance->setStatus(SERVICE_START_PENDING);
        QCoreApplication::postEvent(instance->controllerHandler, new QEvent(QEvent::Type(QEvent::User + code)));
        instance->condition.wait(&instance->mutex);
        instance->setStatus(SERVICE_RUNNING);
        break;
    case SERVICE_CONTROL_STOP: // 1
        instance->setStatus(SERVICE_STOP_PENDING);
        QCoreApplication::postEvent(instance->controllerHandler, new QEvent(QEvent::Type(QEvent::User + code)));
        instance->condition.wait(&instance->mutex);
        // status will be reported as stopped by start() when qapp::exec returns
        break;

    case SERVICE_CONTROL_PAUSE: // 2
        instance->setStatus(SERVICE_PAUSE_PENDING);
        QCoreApplication::postEvent(instance->controllerHandler, new QEvent(QEvent::Type(QEvent::User + code)));
        instance->condition.wait(&instance->mutex);
        instance->setStatus(SERVICE_PAUSED);
        break;

    case SERVICE_CONTROL_CONTINUE: // 3
        instance->setStatus(SERVICE_CONTINUE_PENDING);
        QCoreApplication::postEvent(instance->controllerHandler, new QEvent(QEvent::Type(QEvent::User + code)));
        instance->condition.wait(&instance->mutex);
        instance->setStatus(SERVICE_RUNNING);
        break;

    case SERVICE_CONTROL_INTERROGATE: // 4
        break;

    case SERVICE_CONTROL_SHUTDOWN: // 5
        // Don't waste time with reporting stop pending, just do it
        QCoreApplication::postEvent(instance->controllerHandler, new QEvent(QEvent::Type(QEvent::User + SERVICE_CONTROL_STOP)));
        instance->condition.wait(&instance->mutex);
        // status will be reported as stopped by start() when qapp::exec returns
        break;

    default:
        if ( code >= 128 && code <= 255 ) {
            QCoreApplication::postEvent(instance->controllerHandler, new QEvent(QEvent::Type(QEvent::User + code)));
            instance->condition.wait(&instance->mutex);
        }
        break;
    }

    instance->mutex.unlock();

    // Report current status
    if (instance->available() && instance->status.dwCurrentState != SERVICE_STOPPED)
        pSetServiceStatus(instance->serviceStatus, &instance->status);
}

void dtkDistributedServiceSysPrivate::setStatus(DWORD state)
{
    if (!available())
	return;
    status.dwCurrentState = state;
    pSetServiceStatus(serviceStatus, &status);
}

void dtkDistributedServiceSysPrivate::setServiceFlags(dtkDistributedServiceBase::ServiceFlags flags)
{
    if (!available())
        return;
    status.dwControlsAccepted = serviceFlags(flags);
    pSetServiceStatus(serviceStatus, &status);
}

DWORD dtkDistributedServiceSysPrivate::serviceFlags(dtkDistributedServiceBase::ServiceFlags flags) const
{
    DWORD control = 0;
    if (flags & dtkDistributedServiceBase::CanBeSuspended)
        control |= SERVICE_ACCEPT_PAUSE_CONTINUE;
    if (!(flags & dtkDistributedServiceBase::CannotBeStopped))
        control |= SERVICE_ACCEPT_STOP;
    if (flags & dtkDistributedServiceBase::NeedsStopOnShutdown)
        control |= SERVICE_ACCEPT_SHUTDOWN;

    return control;
}

class HandlerThread : public QThread
{
public:
    HandlerThread(void) : success(true), console(false), QThread() {}

    bool calledOk(void) { return success; }
    bool runningAsConsole(void) { return console; }

protected:
    bool success, console;

    void run(void)
    {
        SERVICE_TABLE_ENTRYW st [2];
        st[0].lpServiceName = (wchar_t*)dtkDistributedServiceBase::instance()->serviceName().utf16();
        st[0].lpServiceProc = dtkDistributedServiceSysPrivate::serviceMain;
        st[1].lpServiceName = 0;
        st[1].lpServiceProc = 0;
        
        success = (pStartServiceCtrlDispatcher((const SERVICE_TABLE_ENTRY *)st) != 0); // should block
        
        if (!success) {
            if (GetLastError() == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT) {
                // Means we're started from console, not from service mgr
                // start() will ask the mgr to start another instance of us as a service instead
                console = true;
            }
            else {
                dtkDistributedServiceBase::instance()->logMessage(QString("The Service failed to start [%1]").arg(qt_error_string(GetLastError())), dtkDistributedServiceBase::Error);
            }
            dtkDistributedServiceSysPrivate::instance->startSemaphore.release();  // let start() continue, since serviceMain won't be doing it
        }
    }
};

/*
  Ignore WM_ENDSESSION system events, since they make the dtkDistributed kernel quit
*/

bool myEventFilter(void* message, long* result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    if (!msg || (msg->message != WM_ENDSESSION) || !(msg->lParam & ENDSESSION_LOGOFF))
        return dtkDistributedServiceSysPrivate::nextFilter ? dtkDistributedServiceSysPrivate::nextFilter(message, result) : false;

    if (dtkDistributedServiceSysPrivate::nextFilter)
        dtkDistributedServiceSysPrivate::nextFilter(message, result);
    if (result)
        *result = TRUE;
    return true;
}

/* There are three ways we can be started:

   - By a service controller (e.g. the Services control panel), with
   no (service-specific) arguments. ServiceBase::exec() will then call
   start() below, and the service will start.

   - From the console, but with no (service-specific) arguments. This
   means we should ask a controller to start the service (i.e. another
   instance of this executable), and then just terminate. We discover
   this case (as different from the above) by the fact that
   StartServiceCtrlDispatcher will return an error, instead of blocking.

   - From the console, with -e(xec) argument. ServiceBase::exec() will
   then call ServiceBasePrivate::exec(), which calls
   ServiceBasePrivate::run(), which runs the application as a normal
   program.
*/

bool dtkDistributedServiceBasePrivate::start(void)
{
    sysInit();
    if (!winServiceInit())
        return false;

    // Since StartServiceCtrlDispatcher() blocks waiting for service
    // control events, we need to call it in another thread, so that
    // the main thread can run the QApplication event loop.
    HandlerThread* ht = new HandlerThread();
    ht->start();

    dtkDistributedServiceSysPrivate* sys = dtkDistributedServiceSysPrivate::instance;

    // Wait until service args have been received by serviceMain.
    // If Windows doesn't call serviceMain (or
    // StartServiceControlDispatcher doesn't return an error) within
    // a timeout of 20 secs, something is very wrong; give up
    if (!sys->startSemaphore.tryAcquire(1, 20000))
        return false;

    if (!ht->calledOk()) {
        if (ht->runningAsConsole())
            return controller.start(args.mid(1));
        else
            return false;
    }

    int argc = sys->serviceArgs.size();
    QVector<char *> argv(argc);
    QList<QByteArray> argvData;
    for (int i = 0; i < argc; ++i)
        argvData.append(sys->serviceArgs.at(i).toLocal8Bit());
    for (int i = 0; i < argc; ++i)
        argv[i] = argvData[i].data();

    q_ptr->createApplication(argc, argv.data());
    QCoreApplication *app = QCoreApplication::instance();
    if (!app)
        return false;

    dtkDistributedServiceSysPrivate::nextFilter = app->setEventFilter(myEventFilter);

    sys->controllerHandler = new dtkDistributedServiceControllerHandler(sys);
    sys->startSemaphore2.release(); // let serviceMain continue (and end)
    sys->status.dwWin32ExitCode = q_ptr->executeApplication();
    sys->setStatus(SERVICE_STOPPED);

    if (ht->isRunning())
        ht->wait(1000);         // let the handler thread finish

    delete sys->controllerHandler;
    sys->controllerHandler = 0;

    if (ht->isFinished())
        delete ht;

    delete app;

    sysCleanup();

    return true;
}

bool dtkDistributedServiceBasePrivate::install(const QString &account, const QString &password)
{
    bool result = false;
    if (!winServiceInit())
        return result;

    // Open the Service Control Manager
    SC_HANDLE hSCM = pOpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
    if (hSCM) {
        QString acc = account;
        DWORD dwStartType = startupType == dtkDistributedServiceController::AutoStartup ? SERVICE_AUTO_START : SERVICE_DEMAND_START;
        DWORD dwServiceType = SERVICE_WIN32_OWN_PROCESS;
        wchar_t *act = 0;
        wchar_t *pwd = 0;
        if (!acc.isEmpty()) {
            // The act string must contain a string of the format "Domain\UserName",
            // so if only a username was specified without a domain, default to the local machine domain.
            if (!acc.contains(QChar('\\'))) {
                acc.prepend(QLatin1String(".\\"));
            }
            if (!acc.endsWith(QLatin1String("\\LocalSystem")))
                act = (wchar_t*)acc.utf16();
        }
        if (!password.isEmpty() && act) {
            pwd = (wchar_t*)password.utf16();
        }

        // Only set INTERACTIVE if act is LocalSystem. (and act should be 0 if it is LocalSystem).
        if (!act) dwServiceType |= SERVICE_INTERACTIVE_PROCESS;

        // Create the service
        SC_HANDLE hService = pCreateService(hSCM, (LPCTSTR)controller.serviceName().utf16(),
                                            (LPCTSTR)controller.serviceName().utf16(),
                                            SERVICE_ALL_ACCESS,
                                            dwServiceType, // QObject::inherits ( const char * className ) for no inter active ????
                                            dwStartType, SERVICE_ERROR_NORMAL, (LPCTSTR)filePath().utf16(),
                                            0, 0, 0,
                                            (LPCTSTR)act, (LPCTSTR)pwd);
        if (hService) {
            result = true;
            if (!serviceDescription.isEmpty()) {
                SERVICE_DESCRIPTION sdesc;
                sdesc.lpDescription = (LPSTR)serviceDescription.utf16();
                pChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &sdesc);
            }
            pCloseServiceHandle(hService);
        }
        pCloseServiceHandle(hSCM);
    }
    return result;
}

QString dtkDistributedServiceBasePrivate::filePath(void) const
{
    wchar_t path[_MAX_PATH];
    ::GetModuleFileNameW( 0, path, sizeof(path) );
    return QString::fromUtf16((unsigned short*)path);
}

bool dtkDistributedServiceBasePrivate::sysInit()
{
    sysd = new dtkDistributedServiceSysPrivate();

    sysd->serviceStatus			    = 0;
    sysd->status.dwServiceType		    = SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS;
    sysd->status.dwCurrentState		    = SERVICE_STOPPED;
    sysd->status.dwControlsAccepted         = sysd->serviceFlags(serviceFlags);
    sysd->status.dwWin32ExitCode	    = NO_ERROR;
    sysd->status.dwServiceSpecificExitCode  = 0;
    sysd->status.dwCheckPoint		    = 0;
    sysd->status.dwWaitHint		    = 0;

    return true;
}

void dtkDistributedServiceBasePrivate::sysSetPath(void)
{

}

void dtkDistributedServiceBasePrivate::sysCleanup(void)
{
    if (sysd) {
        delete sysd;
        sysd = 0;
    }
}

void dtkDistributedServiceBase::setServiceFlags(ServiceFlags flags)
{
    if (d_ptr->serviceFlags == flags)
        return;

    d_ptr->serviceFlags = flags;

    if (d_ptr->sysd)
        d_ptr->sysd->setServiceFlags(flags);
}

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
***********************************************************************/
