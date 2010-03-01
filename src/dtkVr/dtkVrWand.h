/* dtkVrWand.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 21 18:27:56 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 24 19:27:51 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 33
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

    enum Action {
        dtkVrWandPicking,
        dtkVrWandNone
    };

    enum Mode {
        dtkVrWandInteraction,
        dtkVrWandNavigation
    };

    int& action(void);
    int& mode(void);

    dtkVec3& referencePosition(void);
    dtkQuat& referenceOrientation(void);
    dtkVec3& currentPosition(void);
    dtkQuat& currentOrientation(void);

    void setAction(Action action);
    void setMode(Mode mode);

    void setReferencePosition(const dtkVec3& position);
    void setReferenceOrientation(const dtkQuat& orientation);
    void setCurrentPosition(const dtkVec3& position);
    void setCurrentOrientation(const dtkQuat& orientation);

private:
    dtkVrWandPrivate *d;
};

#endif
