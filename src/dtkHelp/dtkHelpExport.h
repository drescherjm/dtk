/* dtkHelpExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 19:59:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 19:59:02 2010 (+0100)
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
    #ifdef dtkHelp_EXPORTS
        #define DTKHELP_EXPORT __declspec(dllexport) 
    #else
        #define DTKHELP_EXPORT __declspec(dllimport)
    #endif
#else
    #define DTKHELP_EXPORT	
#endif
