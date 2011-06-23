/* dtkZipExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Sep  9 11:29:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 21 12:16:50 2011 (+0200)
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
