/* dtkComposerExport.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:36:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 10:37:16 2012 (+0100)
 *           By: tkloczko
 *     Update #: 1
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
