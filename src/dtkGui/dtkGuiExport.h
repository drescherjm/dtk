/* dtkGuiExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Mar 13 21:49:35 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:21:38 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKGUIEXPORT_H
#define DTKGUIEXPORT_H

#ifdef WIN32
    #ifdef dtkGui_EXPORTS
        #define DTKGUI_EXPORT __declspec(dllexport) 
    #else
        #define DTKGUI_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKGUI_EXPORT	
#endif

#endif
