/* dtkCryptoExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan  7 16:26:20 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Jan  7 16:26:47 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifdef WIN32
    #ifdef dtkCrypto_EXPORTS
        #define DTKCRYPTO_EXPORT __declspec(dllexport) 
    #else
        #define DTKCRYPTO_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKCRYPTO_EXPORT	
#endif
