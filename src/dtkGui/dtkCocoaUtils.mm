/* dtkCocoaUtils.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 17 09:48:36 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 17 11:30:42 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <Carbon/Carbon.h>
#include <Cocoa/Cocoa.h>
#include <QString>

void setBufferFromCFString(QString& qs, CFStringRef cfs)
{
    if (!cfs)
        return;

    CFIndex size = CFStringGetLength(cfs);
    UniChar fixedSizeBuffer[1024];
    UniChar *buffer;

    if (size > (CFIndex)(sizeof(fixedSizeBuffer) / sizeof(UniChar))) {
        buffer = (UniChar *)malloc(size * sizeof(UniChar));
    } else {
        buffer = fixedSizeBuffer;
    }

    CFStringGetCharacters(cfs, CFRangeMake (0, size), buffer);

    qs.setUnicode((const QChar *)buffer, (uint)size);

    if (buffer != fixedSizeBuffer)
        free(buffer);
}

QString qStringfromCFString(CFStringRef cfs)
{
    QString qs;
    setBufferFromCFString(qs, cfs);
    return qs;
}

QString qStringfromNSString(NSString *nss)
{
    QString qs;
    setBufferFromCFString(qs, (CFStringRef)nss);
    return qs;
}

// /////////////////////////////////////////////////////////////////
// CREDITS
// /////////////////////////////////////////////////////////////////

/*
 * Copyright (C) 2004 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */
