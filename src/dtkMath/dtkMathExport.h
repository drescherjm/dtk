/* dtkMathExport.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Sep  9 11:29:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  9 11:30:14 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKMATHEXPORT_H
#define DTKMATHEXPORT_H

#ifdef WIN32
    #ifdef dtkMath_EXPORTS
        #define DTKMATH_EXPORT __declspec(dllexport) 
    #else
        #define DTKMATH_EXPORT __declspec(dllimport)
    #endif
#else
    #define DTKMATH_EXPORT	
#endif

#endif
