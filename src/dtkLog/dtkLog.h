/* dtkLog.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 14:37:36 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  1 21:20:39 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 126
 */

/* Commentary: See credits at EOF.
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKLOG_H
#define DTKLOG_H

namespace dtkLog
{
    enum Level {
        Trace = 0x000,
        Debug = 0x001,
         Info = 0x010,
         Warn = 0x011,
        Error = 0x100,
        Fatal = 0x101
    };
}

#include "dtkLogger.h"
#include "dtkLogDestination.h"
#include "dtkLogEngine.h"

// /////////////////////////////////////////////////////////////////
// Trace level stream
// /////////////////////////////////////////////////////////////////

#define dtkTrace()                                                      \
    if (dtkLogger::instance().level() > dtkLog::Trace)                  \
        ;                                                               \
    else                                                                \
        dtkLogEngine(dtkLog::Trace).stream()

// /////////////////////////////////////////////////////////////////
// Debug level stream
// /////////////////////////////////////////////////////////////////

#define dtkDebug()                                                      \
    if (dtkLogger::instance().level() > dtkLog::Debug)                  \
        ;                                                               \
    else                                                                \
        dtkLogEngine(dtkLog::Debug).stream()

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#define dtkInfo()                                                       \
    if (dtkLogger::instance().level() > dtkLog::Info)                   \
        ;                                                               \
    else                                                                \
        dtkLogEngine(dtkLog::Info).stream()

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#define dtkWarn()                                                       \
    if (dtkLogger::instance().level() > dtkLog::Warn)                   \
        ;                                                               \
    else                                                                \
        dtkLogEngine(dtkLog::Warn).stream()

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#define dtkError()                                                      \
    if (dtkLogger::instance().level() > dtkLog::Error)                  \
        ;                                                               \
    else                                                                \
        dtkLogEngine(dtkLog::Error).stream()

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#define dtkFatal()                                                      \
        dtkLogEngine(dtkLog::Fatal).stream()

// /////////////////////////////////////////////////////////////////

#endif

// /////////////////////////////////////////////////////////////////
// Credits
// /////////////////////////////////////////////////////////////////

// Copyright (c) 2010, Razvan Petru
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:

// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in
//   the documentation and/or other materials provided with the
//   distribution.

// * The name of the contributors may not be used to endorse or
//   promote products derived from this software without specific
//   prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
