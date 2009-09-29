/* dtkCocoaController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 13 18:47:58 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 29 22:18:22 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOCOACONTROLLER_H
#define DTKCOCOACONTROLLER_H

class dtkCocoaControllerPrivate;

class dtkCocoaController
{
public:
    static dtkCocoaController *instance(void);

    void   initialize(void);
    void uninitialize(void);

protected:
    dtkCocoaController(void);
   ~dtkCocoaController(void);

private:
   static dtkCocoaController *s_instance;

private:
   dtkCocoaControllerPrivate *d;
};

#endif
