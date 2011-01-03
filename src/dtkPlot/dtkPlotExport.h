/* dtkPlotExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Sep  9 11:29:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Nov 22 10:21:53 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTEXPORT_H
#define DTKPLOTEXPORT_H

#ifdef WIN32
    #ifdef dtkPlot_EXPORTS
        #define DTKPLOT_EXPORT __declspec(dllexport) 
    #else
        #define DTKPLOT_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DTKPLOT_EXPORT	
#endif

#endif
