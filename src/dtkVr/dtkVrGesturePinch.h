/* dtkVrGesturePinch.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Oct 23 17:34:30 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Oct 23 17:45:14 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRGESTUREPINCH_H
#define DTKVRGESTUREPINCH_H

#include <QtGui/QPinchGesture>

class dtkVrGesturePinchPrivate;

class dtkVrGesturePinch : public QPinchGesture
{
    Q_OBJECT

public:
     dtkVrGesturePinch(QObject *parent);
    ~dtkVrGesturePinch(void);

    Qt::GestureState state(void) const;

public:
    void setState(Qt::GestureState state);

private:
    dtkVrGesturePinchPrivate *d;
};

#endif
