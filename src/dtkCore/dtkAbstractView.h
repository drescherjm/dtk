/* dtkAbstractView.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:00:26 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 19:16:24 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 286
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

public slots:
    virtual void   link(dtkAbstractView *other);
    virtual void unlink(dtkAbstractView *other);

    virtual void   select(dtkAbstractData *data);
    virtual void unselect(dtkAbstractData *data);

    virtual void setStereo(bool on);

    virtual void setView(void *view);

    virtual void setData(dtkAbstractData *data);
    virtual void setData(dtkAbstractData *data, int inputId);

    virtual void setBackgroundColor(int red, int green, int blue);
    virtual void setBackgroundColor(double red, double green, double blue);

    virtual void *view(void);
    virtual void *data(void);
    virtual void *data(int channel);

    virtual bool stereo(void);

    virtual void  clear(void);
    virtual void  reset(void);
    virtual void update(void);

    virtual QWidget *widget(void);
    
    virtual void close(void);

    void showFullScreen(void);
    void showMinimized(void);
    void showMaximized(void);
    void showNormal(void);
    void show(void);

    void resize(int width, int height);

    void addAnimator  (dtkAbstractViewAnimator   *animator);
    void addNavigator (dtkAbstractViewNavigator  *navigator);
    void addInteractor(dtkAbstractViewInteractor *interactor);

    void  enableAnimator(const QString& animator);
    void disableAnimator(const QString& animator);

    void  enableNavigator(const QString& navigator);
    void disableNavigator(const QString& navigator);

    void  enableInteractor(const QString& interactor);
    void disableInteractor(const QString& interactor);

    dtkAbstractViewAnimator   *animator  (const QString& type);
    dtkAbstractViewNavigator  *navigator (const QString& type);
    dtkAbstractViewInteractor *interactor(const QString& type);

    QList<dtkAbstractViewAnimator   *> animators(void) const;
    QList<dtkAbstractViewNavigator  *> navigators(void) const;
    QList<dtkAbstractViewInteractor *> interactors(void) const;

    virtual void   initialize(void);
    virtual void uninitialize(void);

    virtual void  enableInteraction(void);
    virtual void disableInteraction(void);

    virtual void bounds(float& xmin, float& xmax, float& ymin, float& ymax, float &zmin, float& zmax);

    virtual void cameraUp(double *coordinates) const;
    virtual void cameraPosition(double *coordinates) const;
    virtual void cameraFocalPoint(double *coordinates) const;

    virtual void setCameraPosition(double x, double y, double z);

    virtual void setCameraClippingRange(double near, double far);

    virtual QString cameraProjectionMode(void) const;
    virtual double cameraViewAngle(void) const;
    virtual double cameraZoom(void) const;

private:
    DTK_DECLARE_PRIVATE(dtkAbstractView);
};

DTKCORE_EXPORT QDebug operator<<(QDebug debug, const dtkAbstractView& viewer);
DTKCORE_EXPORT QDebug operator<<(QDebug debug,       dtkAbstractView *viewer);

#endif
