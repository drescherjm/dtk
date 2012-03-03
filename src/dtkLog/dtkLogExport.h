/* dtkLogExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 14:38:12 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  1 14:38:35 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKLOGEXPORT_H
#define DTKLOGEXPORT_H

#ifdef WIN32
    #ifdef dtkLog_EXPORTS
        #define DTKLOG_EXPORT __declspec(dllexport) 
    #else
        #define DTKLOG_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKLOG_EXPORT	
#endif

#endif
