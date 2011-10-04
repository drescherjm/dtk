/* dtkZipExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Sep 23 10:43:26 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 23 10:44:18 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKZIPEXPORT_H
#define DTKZIPEXPORT_H

#ifdef WIN32
    #ifdef dtkZip_EXPORTS
        #define DTKZIP_EXPORT __declspec(dllexport) 
    #else
        #define DTKZIP_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKZIP_EXPORT	
#endif

#endif
