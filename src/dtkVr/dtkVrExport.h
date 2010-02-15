/* dtkVrExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jan 13 14:01:37 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:20:24 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVREXPORT_H
#define DTKVREXPORT_H

#ifdef WIN32
    #ifdef dtkVr_EXPORTS
        #define DTKVR_EXPORT __declspec(dllexport) 
    #else
        #define DTKVR_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKVR_EXPORT	
#endif

#endif
