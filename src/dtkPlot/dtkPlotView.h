/* dtkPlotView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:02:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 15 12:16:33 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 77
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEW_H
#define DTKPLOTVIEW_H

#include "dtkPlotExport.h"

#include <dtkCore/dtkAbstractView.h>

#include <QtCore>
#include <QtGui>

class dtkPlotCurve;
class dtkPlotViewPrivate;

class DTKPLOT_EXPORT dtkPlotView : public dtkAbstractView
{
    Q_OBJECT

public:
    enum Scale {
        Linear,
        Logarithmic
    };

public:
     dtkPlotView(void);
    ~dtkPlotView(void);

public:
     QList<dtkPlotCurve *> curves(void);

public:
    void   activatePanning(void);
    void deactivatePanning(void);

    void   activatePicking(void);
    void deactivatePicking(void);

    void   activateZooming(void);
    void deactivateZooming(void);

public:
    void zoomForward(void);
    void zoomBackward(void);

public:
    void setAxisTitleX(const QString& title);
    void setAxisTitleY(const QString& title);
    
    void setAxisScaleX(double min, double max);
    void setAxisScaleY(double min, double max);

    void setAxisScaleX(Scale scale);
    void setAxisScaleY(Scale scale);

    void setStyleSheet(const QString& sheet);
    
public:
    virtual void setBackgroundColor(int red, int green, int blue);
    virtual void setBackgroundColor(double red, double green, double blue);
    virtual void setBackgroundColor(const QColor& color);
    virtual QColor BackgroundColor() const;

    
public:
    dtkPlotView& operator<<(dtkPlotCurve *curve);

public slots:
    void update(void);

public slots:
    QWidget *widget(void);

signals:
    void zoomForwardEnabled(bool);
    void zoomBackwardEnabled(bool);

private:
    friend class dtkPlotCurve;
    friend class dtkPlotRenderer;

private:
    dtkPlotViewPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

DTKCORE_EXPORT dtkAbstractView *createPlotView(void);

#endif
