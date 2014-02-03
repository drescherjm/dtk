/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan  7 14:27:57 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Jan  7 16:22:35 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>

#include <dtkCrypto/dtkCryptoLicenseManager.h>

int main(int argc, char **argv)
{
    if(argc != 2) {
        qDebug() << "Usage:" << argv[0] << "file.license";
        return 1;
    }

    dtkCryptoLicenseManager::instance()->setKey("0xA16104C150FD1305368F7394D1FD7E59618CE5008682ED131B71583B192E12EBCE252FD610798AC1332FDC43C358FA70713548A8E284D4F0EF1E319EB1D91AE1A93D94A1047C25473ABB64CC0BF5718A69E0D045EB308EE0571A732EAA1C186060F7DCBE6637BF71EF747290EE4B74448291BA62F6BB2E0E9E0CC47C57D7CA01");

    dtkCryptoLicenseManager::instance()->blacklist("eab80db0a8fd76c044a2c89e20c9014454ead53e");
    
    if(dtkCryptoLicenseManager::instance()->check(argv[1]))
        qDebug() << "Software registered to" << dtkCryptoLicenseManager::instance()->dictionary(argv[1]).value("Name");
    else
        qDebug() << "Software not registered";

    return 0;
}
