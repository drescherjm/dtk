/* dtkCocoaUtils.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jul 22 16:40:48 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jul 22 16:41:18 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOCOAUTILS_H
#define DTKCOCOAUTILS_H

void setBufferFromCFString(QString& qs, CFStringRef cfs);

QString qStringfromCFString(CFStringRef cfs);
QString qStringfromNSString(NSString *nss);

#endif
