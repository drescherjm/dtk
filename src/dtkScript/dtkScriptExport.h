/* dtkScriptExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Mar 13 21:41:58 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:22:20 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSCRIPTEXPORT_H
#define DTKSCRIPTEXPORT_H

#ifdef WIN32
    #ifdef dtkScript_EXPORTS
        #define DTKSCRIPT_EXPORT __declspec(dllexport) 
    #else
        #define DTKSCRIPT_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKSCRIPT_EXPORT	
#endif

#endif
