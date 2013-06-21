/* dtkPlotView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:02:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun 21 15:19:31 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 114
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

#include "dtkPlotViewLegend.h"

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

   enum LegendPosition {
        LeftLegend,
        RightLegend,
        BottomLegend,
        TopLegend
    };

public:
     dtkPlotView(void);
    ~dtkPlotView(void);

public:
    void clear(void);

public:
     QList<dtkPlotCurve *> curves(void);

public:
    void   activatePanning(void);
    void deactivatePanning(void);

    void   activatePicking(void);
    void deactivatePicking(void);

    void   activateZooming(void);
    void deactivateZooming(void);

    void   activateGrid(void);
    void deactivateGrid(void);

    void   activateLegend(void);
    void deactivateLegend(void);

public:
    void zoomForward(void);
    void zoomBackward(void);

public:
    void setTitle(const QString&);
    void setTitleSize(const int&);

    void setAxisTitleX(const QString& title);
    void setAxisTitleY(const QString& title);

    void setAxisTitleSizeX(const int&);
    void setAxisTitleSizeY(const int&);

    void setAxisScaleX(double min, double max);
    void setAxisScaleY(double min, double max);

    void setAxisScaleX(Scale scale);
    void setAxisScaleY(Scale scale);

    void setLegendPosition(LegendPosition position);

    void fillCurveArea(int alpha);

    void setStyleSheet(const QString& sheet);

public:
    QString title(void) const;
    int titleSize(void) const;

    QString axisTitleX(void) const;
    QString axisTitleY(void) const;

    int axisTitleSizeX(void) const;
    int axisTitleSizeY(void) const;

    void setGridColor(const QColor& color);
    void setZoomColor(const QColor& color);

    void updateAxes(void);
    
public:
    void setBackgroundColor(int red, int green, int blue);
    void setBackgroundColor(double red, double green, double blue);
    void setBackgroundColor(const QColor& color);
    QColor backgroundColor(void) const;

    void setForegroundColor(const QColor& color);
    QColor foregroundColor(void) const;

    void updateColors(void);

public:
    QWidget *plotWidget(void);

    QWidget *widget(void);

public:
    dtkPlotView& operator<<(dtkPlotCurve *curve);

public slots:
    void update(void);

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
