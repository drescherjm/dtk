/* dtkComposerExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:46:14 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 13:46:41 2009 (+0200)
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
    #ifdef dtkComposer_EXPORTS
        #define DTKCOMPOSER_EXPORT __declspec(dllexport) 
    #else
        #define DTKCOMPOSER_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKCOMPOSER_EXPORT	
#endif
