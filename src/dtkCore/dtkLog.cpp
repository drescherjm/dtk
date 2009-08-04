/* dtkLog.cpp --- 
 * 
 * Author: Jean-Christophe Lombardo
 * Copyright (C) 2008-2009 - Jean-Christophe Lombardo, Inria.
 * Created: Thu May 14 14:32:46 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug  4 12:20:30 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 111
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkLog.h"

QMultiMap<QString, dtkLog::Handler> dtkLog::s_handlers;

// /////////////////////////////////////////////////////////////////
// dtkStandardRedirector
// /////////////////////////////////////////////////////////////////

#include <iostream>
#include <streambuf>
#include <string>

class dtkStandardRedirector : public std::basic_streambuf<char>
{
public:
    enum Channel { Out, Err, Log } ;

     dtkStandardRedirector(std::ostream &stream, Channel channel);
    ~dtkStandardRedirector(void);
	
    static bool   initialize(void);
    static void uninitialize(void);

protected:
    virtual int overflow(int v);    
    virtual std::streamsize xsputn(const char *p, std::streamsize n);

    void flush(void);

private:
    std::ostream&   m_stream;
    std::streambuf *m_buffer;
    std::string     m_string;
    Channel         m_channel;

    static dtkStandardRedirector *s_err;
    static dtkStandardRedirector *s_out;
    static dtkStandardRedirector *s_log;
};

dtkStandardRedirector *dtkStandardRedirector::s_err = 0l;
dtkStandardRedirector *dtkStandardRedirector::s_out = 0l;
dtkStandardRedirector *dtkStandardRedirector::s_log = 0l;

dtkStandardRedirector::dtkStandardRedirector(std::ostream &stream, Channel channel) : m_stream(stream), m_channel(channel)
{
    m_string = " ";
    m_buffer = stream.rdbuf();
    stream.rdbuf(this);
}

dtkStandardRedirector::~dtkStandardRedirector(void)
{
    if (!m_string.empty()) flush();

    m_stream.rdbuf(m_buffer);
}

void dtkStandardRedirector::flush(void)
{
    switch(m_channel) {
    case Err: 
        dtkLog::error() << QString::fromStdString(m_string);
        break;
    case Out: 
    case Log: 
        dtkLog::output() << QString::fromStdString(m_string);
        break;
    default:
        break;
    };
}

int dtkStandardRedirector::overflow(int v)
{
    if (v == '\n') {
        dtkLog::output() << m_string.c_str();
        m_string.erase(m_string.begin(), m_string.end());
    } else
        m_string += v;
    
    return v;
}

std::streamsize dtkStandardRedirector::xsputn(const char *p, std::streamsize n)
{
    if(p)
        m_string += QString::fromAscii(p, n).remove('\n').remove('\r').simplified().toStdString();

    return n;
}

bool dtkStandardRedirector::initialize(void)
{
    if (!s_err) s_err = new dtkStandardRedirector(std::cerr, dtkStandardRedirector::Err);
    if (!s_out) s_out = new dtkStandardRedirector(std::cout, dtkStandardRedirector::Out);
    if (!s_log) s_log = new dtkStandardRedirector(std::clog, dtkStandardRedirector::Log);
    return true;
}

void dtkStandardRedirector::uninitialize(void)
{
    if (s_err) { delete s_err; s_err = 0l; }
    if (s_out) { delete s_out; s_out = 0l; }
    if (s_log) { delete s_log; s_log = 0l; }
}

static bool log_initialized = dtkStandardRedirector::initialize();

// /////////////////////////////////////////////////////////////////
// dtkLog
// /////////////////////////////////////////////////////////////////

dtkLog& dtkLog::operator<<(int value)
{
    m_log += QString::number(value);
    
    return *this;
}

dtkLog& dtkLog::operator<<(float value)
{
    m_log += QString::number(value);

    return *this;
}

dtkLog& dtkLog::operator<<(double value)
{
    m_log += QString::number(value);

    return *this;
}

dtkLog& dtkLog::operator<<(QString value)
{ 
    m_log += value;

    return *this;
}

dtkLog dtkLog::output(QString source)
{
    return dtkLog(source, Output);
}

dtkLog dtkLog::error(QString source)
{
    return dtkLog(source, Error);
}

dtkLog dtkLog::debug(QString source)
{
    return dtkLog(source, Debug);
}

dtkLog dtkLog::warning(QString source)
{
    return dtkLog(source, Warning);
}

dtkLog dtkLog::critical(QString source)
{
    return dtkLog(source, Critical);
}

dtkLog dtkLog::fatal(QString source)
{
    return dtkLog(source, Fatal);
}

dtkLog::dtkLog(QString source, Level level) : m_level(level), m_source(source)
{

}

dtkLog::~dtkLog(void)
{
     if (s_handlers.keys().contains(m_source))
         foreach(Handler handler, s_handlers.values(m_source)) handler(m_level, m_log);
    else
        qDebug().nospace() << QDate::currentDate().toString().toAscii().constData() << QTime::currentTime().toString().toAscii() << "(" << m_source << ") Level=" << m_level << "-" << m_log.toAscii();
}

void dtkLog::registerHandler(Handler handler, QString source)
{
    s_handlers.insert(source, handler);
}

void dtkLog::unregisterHandler(Handler handler, QString source)
{
    s_handlers.remove(source, handler);
}

void dtkLog::disableRedirection(void)
{
    dtkStandardRedirector::uninitialize();
}

// /////////////////////////////////////////////////////////////////
// dtkLogEvent
// /////////////////////////////////////////////////////////////////

dtkLogEvent::dtkLogEvent(dtkLog::Level level, const QString& message) : QEvent(s_type)
{
    this->m_level = level;
    this->m_message = message;
}

dtkLog::Level dtkLogEvent::level(void) const
{
    return m_level;
}

QString dtkLogEvent::message(void) const
{
    return m_message;
}

QEvent::Type dtkLogEvent::s_type = static_cast<Type>(QEvent::registerEventType());

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

DTKCORE_EXPORT dtkLog dtkOutput(void)
{
    return dtkLog::output();
}

DTKCORE_EXPORT dtkLog dtkError(void)
{
    return dtkLog::error();
}

DTKCORE_EXPORT dtkLog dtkDebug(void)
{
    return dtkLog::debug();
}

DTKCORE_EXPORT dtkLog dtkWarning(void)
{
    return dtkLog::warning();
}

DTKCORE_EXPORT dtkLog dtkCritical(void)
{
    return dtkLog::critical();
}

DTKCORE_EXPORT dtkLog dtkFatal(void)
{
    return dtkLog::fatal();
}
