/* dtkCryptoLicenseManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan  7 10:51:40 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Jan  7 15:55:51 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 135
 */

/* Commentary: 
 * 
 * See credits at EOF.
 */

/* Change log:
 * 
 */

#include "dtkCryptoBase64.h"
#include "dtkCryptoLicenseManager.h"

#include <QtXml>

#include <openssl/rsa.h>
#include <openssl/sha.h>

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

const char* CreateCString(std::string output, ...)
{
    static char text[256];
    va_list ap;
    
    va_start(ap, output);
    vsprintf(text, output.c_str(), ap);
    va_end(ap);
    
    return (const char*)text;
}

// /////////////////////////////////////////////////////////////////
// dtkCryptoLicenseManagerPrivate
// /////////////////////////////////////////////////////////////////

class dtkCryptoLicenseManagerPrivate
{
public:
    RSA *rsaKey;
    QString hash;
    QList<QString> blacklist;
};

// /////////////////////////////////////////////////////////////////
// dtkCryptoLicenseManager
// /////////////////////////////////////////////////////////////////

dtkCryptoLicenseManager *dtkCryptoLicenseManager::instance(void)
{
    if(!s_instance)
        s_instance = new dtkCryptoLicenseManager;

    return s_instance;
}

bool dtkCryptoLicenseManager::setKey(const QString& key)
{
    d->hash = "";
	
    d->rsaKey = RSA_new(); BN_hex2bn(&(d->rsaKey)->e, "3");
    
    QString mutableKey = key.toLower();
    
    if(mutableKey.startsWith("0x"))
        BN_hex2bn(&(d->rsaKey)->n, mutableKey.remove(0, 2).toAscii().data());
    else 
        BN_dec2bn(&(d->rsaKey)->n, mutableKey.toAscii().data());
	
    return true;
}

bool dtkCryptoLicenseManager::setHash(const QString& hash)
{
    d->hash = hash;
}

bool dtkCryptoLicenseManager::check(dtkCryptoLicenseData data)
{
    return dictionary(data).size();
}

bool dtkCryptoLicenseManager::check(QString path)
{
    return dictionary(path).size();
}

dtkCryptoLicenseManager::dtkCryptoLicenseData dtkCryptoLicenseManager::dictionary(dtkCryptoLicenseData data)
{
    if (!d->rsaKey->n || !d->rsaKey->e)
        return dtkCryptoLicenseData();

    if (!data.contains("Signature"))
        return dtkCryptoLicenseData();

    unsigned char sigBytes[128];

    if(!b64::b64_decode(data.value("Signature").toAscii().data(), data.value("Signature").length(), sigBytes, 129))
        return dtkCryptoLicenseData();
    
    data.remove(QString("Signature"));
    
    unsigned char checkDigest[128] = {0};
    
    if (RSA_public_decrypt(128, sigBytes, checkDigest, d->rsaKey, RSA_PKCS1_PADDING) != SHA_DIGEST_LENGTH)
        return dtkCryptoLicenseData();

    QString hashCheck;

    for (int hashIndex = 0; hashIndex < SHA_DIGEST_LENGTH; hashIndex++)
        hashCheck += CreateCString("%02x", checkDigest[hashIndex]);

    this->setHash(hashCheck);

    if(d->blacklist.contains(d->hash))
        return dtkCryptoLicenseData();
	
    SHA_CTX ctx; SHA1_Init(&ctx);

    foreach(QString value, data.values())
        SHA1_Update(&ctx, value.toAscii().data(), value.length());

    unsigned char digest[SHA_DIGEST_LENGTH]; SHA1_Final(digest, &ctx);

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) 
        if (checkDigest[i] ^ digest[i])
            return dtkCryptoLicenseData();

    return data;
}

dtkCryptoLicenseManager::dtkCryptoLicenseData dtkCryptoLicenseManager::dictionary(QString path)
{
    dtkCryptoLicenseData data;
    
    QDomDocument doc("license");

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
        return data;

    if (!doc.setContent(&file)) {
        file.close();
        return data;
    }

    file.close();

    QDomElement root = doc.documentElement();
    
    if(!root.isNull() && root.tagName() != "plist")
        return data;

    QDomNode node = root.firstChild();
    
    QDomElement element = node.toElement();
        
    if(!element.isNull() && element.tagName() != "dict")
        return data;
    
    node = node.firstChild();
    
    QString key;
    
    while(!node.isNull()) {
        
        element = node.toElement();
        
        if(!element.isNull() && element.tagName() == "key")
            key = element.text();
        
        if(!element.isNull() && element.tagName() == "string")
            data.insert(key, element.text());
        
        if(!element.isNull() && element.tagName() == "data" && key == "Signature")
            data.insert(key, element.text().simplified().remove(" "));
                
        node = node.nextSibling();
    }
    
    return dictionary(data);
}

QString dtkCryptoLicenseManager::hash(void)
{
    return d->hash;
}

void dtkCryptoLicenseManager::blacklist(const QString& key)
{
    d->blacklist << key;
}

void dtkCryptoLicenseManager::setBlacklist(QList<QString> keys)
{
    d->blacklist = keys;
}

dtkCryptoLicenseManager::dtkCryptoLicenseManager(void)
{
    d = new dtkCryptoLicenseManagerPrivate;
}

dtkCryptoLicenseManager::~dtkCryptoLicenseManager(void)
{
    delete d;

    d = NULL;
}

dtkCryptoLicenseManager *dtkCryptoLicenseManager::s_instance = 0;

// AquaticPrime.cpp
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
