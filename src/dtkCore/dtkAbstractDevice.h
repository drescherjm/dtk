/* dtkAbstractDevice.h --- 
 * 
 * Author: Jean-Christophe Lombardo
 * Copyright (C) 2009 - Jean-Christophe Lombardo, Inria
 * Created: Fri Mar 20 15:24:49 2009
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:52:37 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef _dtkAbstractDevice_h_
#define _dtkAbstractDevice_h_

#include <dtkCore/dtkAbstractObject.h>

class dtkAbstractViewInteractor;
class dtkAbstractViewNavigator;
class dtkAbstractDevicePrivate;

class DTKCORE_EXPORT dtkAbstractDevice : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractDevice(QString name, dtkAbstractObject *parent = 0);
             dtkAbstractDevice(const dtkAbstractDevice& data);
    virtual ~dtkAbstractDevice(void);

    virtual QString description(void) const;
    virtual QString name(void);

    virtual int numOfAxes(void) { return 0; }
    virtual int numOfButtons(void) { return 0; }

    virtual bool button(int idx) { return false; }

    virtual float axis(int idx) { return 0.0f; }

    virtual const float *matrix(void) { return 0l; }

    virtual dtkAbstractViewInteractor *interactor(QString name);
    virtual dtkAbstractViewNavigator *navigator(QString name);

signals:
    void buttonPressed(int idx);
    void buttonReleased(int idx);

protected:
    virtual void setButtonPressed(int idx) { emit buttonPressed(idx); }
    virtual void setButtonReleased(int idx) { emit buttonReleased(idx); }

private:
    dtkAbstractDevicePrivate *d;
};

#endif
