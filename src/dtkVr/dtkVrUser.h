/* dtkVrUser.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 21 18:25:00 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb 21 18:34:53 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRUSER_H
#define DTKVRUSER_H

#include "dtkVrExport.h"

#include <QtCore>

class dtkVec3;
class dtkQuat;
class dtkVrUserPrivate;

class DTKVR_EXPORT dtkVrUser : public QObject
{
    Q_OBJECT

public:
     dtkVrUser(void);
    ~dtkVrUser(void);

    dtkVec3 position(void) const;
    dtkQuat orientation(void) const;

    void setPosition(const dtkVec3& position);
    void setOrientation(const dtkQuat& orientation);

private:
    dtkVrUserPrivate *d;
};

#endif
