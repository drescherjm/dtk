/* dtkJsonExport.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: ven. août  5 10:10:48 2011 (+0200)
 * Version: $Id$
 * Last-Updated: ven. août  5 10:11:20 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 3
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKJSONEXPORT_H
#define DTKJSONEXPORT_H

#ifdef WIN32
#ifdef dtkJson_EXPORTS
#define DTKJSON_EXPORT __declspec(dllexport)
#else
#define DTKJSON_EXPORT __declspec(dllimport)
#endif
#else
#define DTKJSON_EXPORT
#endif

#endif
