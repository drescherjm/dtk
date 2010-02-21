/* dtkVrWand.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 21 18:27:56 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb 21 18:34:57 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRWAND_H
#define DTKVRWAND_H

#include "dtkVrExport.h"

#include <QtCore>

class dtkVec3;
class dtkQuat;
class dtkVrWandPrivate;

class DTKVR_EXPORT dtkVrWand : public QObject
{
    Q_OBJECT

public:
     dtkVrWand(void);
    ~dtkVrWand(void);

    dtkVec3 position(void) const;
    dtkQuat orientation(void) const;

    void setPosition(const dtkVec3& position);
    void setOrientation(const dtkQuat& orientation);

private:
    dtkVrWandPrivate *d;
};

#endif
