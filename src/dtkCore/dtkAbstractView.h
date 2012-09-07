/* dtkAbstractView.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:00:26 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May 23 18:56:31 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 329
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTVIEW_H
#define DTKABSTRACTVIEW_H

#include "dtkAbstractObject.h"

#include <QtGui/QWidget>

class dtkAbstractViewPrivate;
class dtkAbstractViewAnimator;
class dtkAbstractViewNavigator;
class dtkAbstractViewInteractor;
class dtkAbstractData;

#include <dtkMath/dtkVector3D.h>
#include <dtkMath/dtkQuaternion.h>

class DTKCORE_EXPORT dtkAbstractView : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractView(      dtkAbstractView *parent = 0);
	     dtkAbstractView(const dtkAbstractView& other);
    virtual ~dtkAbstractView(void);

public:
    dtkAbstractView& operator = (const dtkAbstractView& other);

public:
    friend DTKCORE_EXPORT QDebug operator<<(QDebug debug, const dtkAbstractView& viewer);
    friend DTKCORE_EXPORT QDebug operator<<(QDebug debug,       dtkAbstractView *viewer);

signals:
    void closed(void);
    void focused(void);

public slots:
    virtual void   link(dtkAbstractView *other);
    virtual void unlink(dtkAbstractView *other);

public slots:
    virtual void   select(dtkAbstractData *data);
    virtual void unselect(dtkAbstractData *data);

public slots:
    virtual void setStereo(bool on);

public slots:
    virtual void setView(void *view);

public slots:
    virtual void setData(dtkAbstractData *data);
    virtual void setData(dtkAbstractData *data, int inputId);

public slots:
    virtual void setBackgroundColor(int red, int green, int blue);
    virtual void setBackgroundColor(double red, double green, double blue);

public slots:
    virtual void *view(void);
    virtual void *data(void);
    virtual void *data(int channel);

public slots:
    virtual bool stereo(void);

public slots:
    virtual void  clear(void);
    virtual void  reset(void);
    virtual void update(void);

public slots:
    virtual QWidget *widget(void);
    
public slots:
    virtual void close(void);

public slots:
    void showFullScreen(void);
    void showMinimized(void);
    void showMaximized(void);
    void showNormal(void);
    void show(void);

public slots:
    void resize(int width, int height);

public slots:
    void addAnimator  (dtkAbstractViewAnimator   *animator);
    void addNavigator (dtkAbstractViewNavigator  *navigator);
    void addInteractor(dtkAbstractViewInteractor *interactor);

public slots:
    void    enableAnimator(const QString& animator);
    void   disableAnimator(const QString& animator);
    void   enableNavigator(const QString& navigator);
    void  disableNavigator(const QString& navigator);
    void  enableInteractor(const QString& interactor);
    void disableInteractor(const QString& interactor);

public slots:
    dtkAbstractViewAnimator   *animator  (const QString& type);
    dtkAbstractViewNavigator  *navigator (const QString& type);
    dtkAbstractViewInteractor *interactor(const QString& type);

public slots:
    QList<dtkAbstractViewAnimator   *> animators(void) const;
    QList<dtkAbstractViewNavigator  *> navigators(void) const;
    QList<dtkAbstractViewInteractor *> interactors(void) const;

public slots:
    virtual void   initialize(void);
    virtual void uninitialize(void);

// /////////////////////////////////////////////////////////////////
// New VR API
// /////////////////////////////////////////////////////////////////

public:
    virtual void setHeadPosition(dtkVector3D<double> position);
    virtual void setHeadOrientation(dtkQuaternion<double> orientation);

public:
    virtual void setUpperLeft(dtkVector3D<double> position);
    virtual void setLowerLeft(dtkVector3D<double> position);
    virtual void setLowerRight(dtkVector3D<double> position);

// /////////////////////////////////////////////////////////////////

private:
    DTK_DECLARE_PRIVATE(dtkAbstractView);
};

DTKCORE_EXPORT QDebug operator<<(QDebug debug, const dtkAbstractView& viewer);
DTKCORE_EXPORT QDebug operator<<(QDebug debug,       dtkAbstractView *viewer);

#endif
