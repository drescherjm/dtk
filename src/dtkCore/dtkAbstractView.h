/* dtkAbstractView.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:00:26 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  1 00:40:53 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 201
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTVIEWER_H
#define DTKABSTRACTVIEWER_H

#include <dtkCore/dtkAbstractObject.h>

class QWidget;

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
	     dtkAbstractView(const dtkAbstractView& view);
    virtual ~dtkAbstractView(void);

    virtual QString description(void) const { return ""; }

    friend QDebug operator<<(QDebug debug, const dtkAbstractView& viewer);
    friend QDebug operator<<(QDebug debug,       dtkAbstractView *viewer);

signals:
    void selected(dtkAbstractData *);

    void clickedScreenCoordinates(int, int);

    void clickedObjectCoordinates(double, double);
    void clickedObjectCoordinates(double, double, double);

    void clickedWorldCoordinates(double, double);
    void clickedWorldCoordinates(double, double, double);

public slots:
    virtual void   link(dtkAbstractView *other) {}
    virtual void unlink(dtkAbstractView *other) {}

    virtual void   select(dtkAbstractData *data) {}
    virtual void unselect(dtkAbstractData *data) {}

    virtual void setView(void *view);

    virtual void setData(dtkAbstractData *data);
    virtual void setData(dtkAbstractData *data, int inputId);

    virtual dtkAbstractData *retreiveAbstractData(void*) { return NULL; }

    virtual void setBackgroundColor(   int red,    int green,    int blue) { DTK_UNUSED(red); DTK_UNUSED(green); DTK_UNUSED(blue); }
    virtual void setBackgroundColor(double red, double green, double blue) { DTK_UNUSED(red); DTK_UNUSED(green); DTK_UNUSED(blue); }

    virtual void setForegroundImage(dtkAbstractData *data) { DTK_UNUSED(data); }
    virtual void setBackgroundImage(dtkAbstractData *data) { DTK_UNUSED(data); }

    virtual void *view(void) { return NULL; }
    virtual void *data(void);
    virtual void *data(int channel);

    virtual void  clear(void) {}
    virtual void  reset(void) {}
    virtual void update(void) {}

    virtual void updatePosition (double x, double y, double z);

    virtual QWidget *widget(void) { return NULL; }

    void showFullScreen(void);
    void showMinimized(void);
    void showMaximized(void);
    void showNormal(void);

    void addAnimator  (dtkAbstractViewAnimator   *animator);
    void addNavigator (dtkAbstractViewNavigator  *navigator);
    void addInteractor(dtkAbstractViewInteractor *interactor);

    void  enableAnimator(QString animator);
    void disableAnimator(QString animator);

    void  enableNavigator(QString navigator);
    void disableNavigator(QString navigator);

    void  enableInteractor(QString interactor);
    void disableInteractor(QString interactor);

    dtkAbstractViewAnimator   *animator  (QString type);
    dtkAbstractViewNavigator  *navigator (QString type);
    dtkAbstractViewInteractor *interactor(QString type);

    void start(unsigned int iterations = 1);
    void stop(void);

    QList<dtkAbstractViewAnimator   *> animators(void);
    QList<dtkAbstractViewNavigator  *> navigators(void);
    QList<dtkAbstractViewInteractor *> interactors(void);

    virtual void setColorLookupTable(int min, int max, int size, int *table) {
        DTK_UNUSED(min);
        DTK_UNUSED(max);
        DTK_UNUSED(size);
        DTK_UNUSED(table);
    }

private:
    dtkAbstractViewPrivate *d;
};

QDebug operator<<(QDebug debug, const dtkAbstractView& viewer);
QDebug operator<<(QDebug debug,       dtkAbstractView *viewer);

#endif
