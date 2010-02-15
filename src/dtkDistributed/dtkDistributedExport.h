/* dtkDistributedExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 09:15:26 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 09:16:42 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDEXPORT_H
#define DTKDISTRIBUTEDEXPORT_H

#ifdef WIN32
    #ifdef dtkDistributed_EXPORTS
        #define DTKDISTRIBUTED_EXPORT __declspec(dllexport) 
    #else
        #define DTKDISTRIBUTED_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKDISTRIBUTED_EXPORT	
#endif

#endif
