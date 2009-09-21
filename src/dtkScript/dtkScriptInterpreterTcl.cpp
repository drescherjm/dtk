/* dtkScriptInterpreterTcl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 26 16:19:44 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep 21 14:03:42 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 300
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkScript/dtkScriptInterpreterTcl.h>

#include <tcl.h>

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterTclPrivate
// /////////////////////////////////////////////////////////////////

class dtkScriptInterpreterTclPrivate
{
public:
    Tcl_Interp *interpreter;
};

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterTcl
// /////////////////////////////////////////////////////////////////

void InitInterpreterChannels(Tcl_Interp *interpreter);

dtkScriptInterpreterTcl::dtkScriptInterpreterTcl(QObject *parent) : dtkScriptInterpreter(parent), d(new dtkScriptInterpreterTclPrivate)
{
    d->interpreter = Tcl_CreateInterp();

    InitInterpreterChannels(d->interpreter);
    
    Tcl_Init(d->interpreter); // -- Initialize built-in tcl functions
    
    this->setVerbose(false);

    int stat;

    // -- Setting up utilities
#ifdef __APPLE__
    interpret("lappend auto_path " + QCoreApplication::applicationDirPath() + "/../../../libraries", &stat);
#else
    interpret("lappend auto_path " + QCoreApplication::applicationDirPath() + "/libraries", &stat);
#endif

    dtkScriptInterpreterTclModuleManager::instance()->initialize(this);

    this->setVerbose(true);
    
    registerPrompt(&prompt);
}

dtkScriptInterpreterTcl::~dtkScriptInterpreterTcl(void)
{
    Tcl_DeleteInterp(d->interpreter);

    delete d;

    d = NULL;
}

Tcl_Interp *dtkScriptInterpreterTcl::interpreter(void)
{
    return d->interpreter;
}

void dtkScriptInterpreterTcl::registerVariable(bool &var, QString name, QString description)
{
    Tcl_LinkVar(d->interpreter, name.toAscii().constData(), (char *)&var, TCL_LINK_BOOLEAN);
    
    registerVariableDescription(name, description);
}

void dtkScriptInterpreterTcl::registerVariable(int &var, QString name, QString description)
{
    Tcl_LinkVar(d->interpreter, name.toAscii().constData(), (char *)&var, TCL_LINK_INT);

    registerVariableDescription(name, description);
}

void dtkScriptInterpreterTcl::registerVariable(double &var, QString name, QString description)
{
    Tcl_LinkVar(d->interpreter, name.toAscii().constData(), (char *)&var, TCL_LINK_DOUBLE);

    registerVariableDescription(name, description);
}

void dtkScriptInterpreterTcl::registerVariable(char *&var, QString name, QString description)
{
    Tcl_LinkVar(d->interpreter, name.toAscii().constData(), (char *)&var, TCL_LINK_STRING);

    registerVariableDescription(name, description);
}

void dtkScriptInterpreterTcl::unregisterVariable(QString name)
{
    Tcl_UnlinkVar(d->interpreter, name.toAscii().constData());

    unregisterVariableDescription(name);
}

QString dtkScriptInterpreterTcl::interpret(const QString& command, int *stat)
{
    int res = Tcl_Eval(d->interpreter, command.toAscii().constData());

    switch(res) {
    case TCL_OK:       *stat = Status_Ok;       break;
    case TCL_ERROR:    *stat = Status_Error;    break;
    case TCL_RETURN:   *stat = Status_Return;   break;
    case TCL_BREAK:    *stat = Status_Break;    break;	
    case TCL_CONTINUE: *stat = Status_Continue; break;
    default: break;
    }

    QString result = QString(Tcl_GetString(Tcl_GetObjResult(d->interpreter)));

    emit interpreted(result, stat);

    dtkScriptInterpreterSynchronizer::instance()->wake();
    
    return "";
}

QString dtkScriptInterpreterTcl::interpret(const QString& command, const QStringList& args, int *stat)
{
    Tcl_Eval(d->interpreter, QString(command + " " + args.join(" ")).toAscii().constData());

    return "";
}

char *dtkScriptInterpreterTcl::prompt(void)
{
    return QString("\033[01;32mtcl\033[00m:\033[01;34m~\033[00m$ ").toAscii().data();
}

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterTclModuleManager
// /////////////////////////////////////////////////////////////////

DTKSCRIPT_EXPORT dtkScriptInterpreterTclModuleManager *dtkScriptInterpreterTclModuleManager::m_instance = NULL;

// /////////////////////////////////////////////////////////////////
// Tcl output channel redirection
// /////////////////////////////////////////////////////////////////

TCL_DECLARE_MUTEX(interpreterMutex)

static  int InterpreterInput  _ANSI_ARGS_((ClientData instanceData,       char *buf, int toRead, int *errorCode));
static  int InterpreterOutput _ANSI_ARGS_((ClientData instanceData, const char *buf, int toWrite, int *errorCode));
static  int InterpreterClose  _ANSI_ARGS_((ClientData instanceData, Tcl_Interp *interp));
static void InterpreterWatch  _ANSI_ARGS_((ClientData instanceData, int mask));
static  int InterpreterHandle _ANSI_ARGS_((ClientData instanceData, int direction, ClientData *handlePtr));

static Tcl_ChannelType interpreterChannelType = {
    (char *)"interpreter",      // Type name.
    NULL,	                // Always non-blocking.
    InterpreterClose,		// Close proc.
    InterpreterInput,		// Input proc.
    InterpreterOutput,		// Output proc.
    NULL,			// Seek proc.
    NULL,			// Set option proc.
    NULL,			// Get option proc.
    InterpreterWatch,		// Watch for events on interpreter.
    InterpreterHandle		// Get a handle from the device.
};

#ifdef __WIN32__

#include <windows.h>

static int ShouldUseInterpreterChannel(int type)
{
    DWORD handleId;
    DCB dcb;
    DWORD interpreterParams;
    DWORD fileType;
    int mode;
    char *bufMode;
    HANDLE handle;

    switch (type) {
	case TCL_STDIN:
	    handleId = STD_INPUT_HANDLE;
	    mode = TCL_READABLE;
	    bufMode = "line";
	    break;
	case TCL_STDOUT:
	    handleId = STD_OUTPUT_HANDLE;
	    mode = TCL_WRITABLE;
	    bufMode = "line";
	    break;
	case TCL_STDERR:
	    handleId = STD_ERROR_HANDLE;
	    mode = TCL_WRITABLE;
	    bufMode = "none";
	    break;
	default:
	    return 0;
	    break;
    }

    handle = GetStdHandle(handleId);

    if ((handle == INVALID_HANDLE_VALUE) || (handle == 0)) {
	return 1;
    }
    fileType = GetFileType(handle);

    if (fileType == FILE_TYPE_CHAR) {
	dcb.DCBlength = sizeof( DCB ) ;
	if (!GetConsoleMode(handle, &interpreterParams) && !GetCommState(handle, &dcb)) {
	    return 1;
	}
    } else if (fileType == FILE_TYPE_UNKNOWN) {
	return 1;
    } else if (Tcl_GetStdChannel(type) == NULL) {
	return 1;
    }

    return 0;
}

#else
#define ShouldUseInterpreterChannel(chan) (1)
#endif

void InitInterpreterChannels(Tcl_Interp *interp)
{
    Tcl_Channel interpreterChannel;

    Tcl_MutexLock(&interpreterMutex);

    static int interpreterInitialized = 0;

    if (!interpreterInitialized) {

	interpreterInitialized = 1;
	
	if (ShouldUseInterpreterChannel(TCL_STDIN)) {
	    interpreterChannel = Tcl_CreateChannel(&interpreterChannelType, "interpreter0", (ClientData) TCL_STDIN, TCL_READABLE);
	    if (interpreterChannel != NULL) {
		Tcl_SetChannelOption(NULL, interpreterChannel, "-translation", "lf");
		Tcl_SetChannelOption(NULL, interpreterChannel, "-buffering", "none");
		Tcl_SetChannelOption(NULL, interpreterChannel, "-encoding", "utf-8");
	    }
	    Tcl_SetStdChannel(interpreterChannel, TCL_STDIN);
	}

	if (ShouldUseInterpreterChannel(TCL_STDOUT)) {
	    interpreterChannel = Tcl_CreateChannel(&interpreterChannelType, "interpreter1", (ClientData) TCL_STDOUT, TCL_WRITABLE);
	    if (interpreterChannel != NULL) {
		Tcl_SetChannelOption(NULL, interpreterChannel, "-translation", "lf");
		Tcl_SetChannelOption(NULL, interpreterChannel, "-buffering", "none");
		Tcl_SetChannelOption(NULL, interpreterChannel, "-encoding", "utf-8");
	    }
	    Tcl_SetStdChannel(interpreterChannel, TCL_STDOUT);
	}
	
	if (ShouldUseInterpreterChannel(TCL_STDERR)) {
	    interpreterChannel = Tcl_CreateChannel(&interpreterChannelType, "interpreter2", (ClientData) TCL_STDERR, TCL_WRITABLE);
	    if (interpreterChannel != NULL) {
		Tcl_SetChannelOption(NULL, interpreterChannel, "-translation", "lf");
		Tcl_SetChannelOption(NULL, interpreterChannel, "-buffering", "none");
		Tcl_SetChannelOption(NULL, interpreterChannel, "-encoding", "utf-8");
	    }
	    Tcl_SetStdChannel(interpreterChannel, TCL_STDERR);
	}
    }
    Tcl_MutexUnlock(&interpreterMutex);
}

#include <iostream>

static int InterpreterOutput(ClientData instanceData, const char *buf, int toWrite, int *errorCode)
{
    *errorCode = 0;

    Tcl_SetErrno(0);

    std::cout << QString(buf).simplified().toAscii().constData() << std::endl;
    
    return toWrite;
}

static int InterpreterInput(ClientData instanceData, char *buf, int bufSize, int *errorCode)
{
    return 0;
}

static int InterpreterClose(ClientData instanceData, Tcl_Interp *interp)
{
    return 0;
}

static void InterpreterWatch(ClientData instanceData, int mask)
{

}

static int InterpreterHandle(ClientData instanceData, int direction, ClientData *handlePtr)
{
    return TCL_ERROR;
}
