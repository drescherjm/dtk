/* dtkCryptoExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan  7 16:26:20 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 09:17:21 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCRYPTOEXPORT_H
#define DTKCRYPTOEXPORT_H

#ifdef WIN32
    #ifdef dtkCrypto_EXPORTS
        #define DTKCRYPTO_EXPORT __declspec(dllexport) 
    #else
        #define DTKCRYPTO_EXPORT __declspec(dllimport)
    #endif
#else
    #define DTKCRYPTO_EXPORT	
#endif

#endif
