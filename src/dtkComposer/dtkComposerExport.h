/* dtkComposerExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:46:14 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:21:59 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREXPORT_H
#define DTKCOMPOSEREXPORT_H

#ifdef WIN32
    #ifdef dtkComposer_EXPORTS
        #define DTKCOMPOSER_EXPORT __declspec(dllexport) 
    #else
        #define DTKCOMPOSER_EXPORT __declspec(dllimport)
    #endif
#else
    #define DTKCOMPOSER_EXPORT	
#endif

#endif
