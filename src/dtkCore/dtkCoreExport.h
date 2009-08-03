/* dtkCoreExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Mar 13 21:19:34 2009 (+0100)
 * Version: $Id$
 * Last-Updated:  Thu Apr  9 18:48:38 2009
 *           By: Jean-Christophe Lombardo
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifdef WIN32
    #ifdef dtkCore_EXPORTS
        #define DTKCORE_EXPORT __declspec(dllexport) 
    #else
        #define DTKCORE_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKCORE_EXPORT	
#endif

