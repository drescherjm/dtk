/* dtkVrExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jan 13 14:01:37 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 13 14:02:05 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifdef WIN32
    #ifdef dtkVr_EXPORTS
        #define DTKVR_EXPORT __declspec(dllexport) 
    #else
        #define DTKVR_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKVR_EXPORT	
#endif
