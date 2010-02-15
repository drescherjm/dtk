/* dtkCoreExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Mar 13 21:19:34 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:20:49 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOREEXPORT_H
#define DTKCOREEXPORT_H

#ifdef WIN32
    #ifdef dtkCore_EXPORTS
        #define DTKCORE_EXPORT __declspec(dllexport) 
    #else
        #define DTKCORE_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKCORE_EXPORT	
#endif

#endif
