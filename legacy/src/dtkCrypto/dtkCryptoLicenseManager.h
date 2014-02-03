/* dtkCryptoLicenseManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan  7 10:48:37 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 20:07:13 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 30
 */

/* Commentary: 
 * 
 * See credits at EOF.
 */

/* Change log:
 * 
 */

#ifndef DTKCRYPTOLICENSEMANAGER_H
#define DTKCRYPTOLICENSEMANAGER_H

#include <QtCore>

#include "dtkCryptoExport.h"

class dtkCryptoLicenseManagerPrivate;

class DTKCRYPTO_EXPORT dtkCryptoLicenseManager
{
    typedef QMap<QString, QString> dtkCryptoLicenseData;

public:
    static dtkCryptoLicenseManager *instance(void);

    bool setKey(const QString& key);
    bool setHash(const QString& hash);

    bool check(dtkCryptoLicenseData data);
    bool check(QString path);

    dtkCryptoLicenseData dictionary(dtkCryptoLicenseData data);
    dtkCryptoLicenseData dictionary(QString path);

    QString hash(void);
    
    void    blacklist(const QString& key);
    void setBlacklist(QList<QString> keys);

protected:
     dtkCryptoLicenseManager(void);
    ~dtkCryptoLicenseManager(void);

private:
    static dtkCryptoLicenseManager *s_instance;

private:
    dtkCryptoLicenseManagerPrivate *d;
};

#endif

// AquaticPrime.h
// AquaticPrime STL Implementation
//
// Copyright (c) 2005, Lucas Newman
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//	¥Redistributions of source code must retain the above copyright notice,
//	 this list of conditions and the following disclaimer.
//	¥Redistributions in binary form must reproduce the above copyright notice,
//	 this list of conditions and the following disclaimer in the documentation and/or
//	 other materials provided with the distribution.
//	¥Neither the name of the Aquatic nor the names of its contributors may be used to 
//	 endorse or promote products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
// FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
// IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
