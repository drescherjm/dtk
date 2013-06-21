/* dtkPlotViewSettings.h --- 
 * 
 * Author: Selim Kraria
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun 21 15:28:38 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 68
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEWSETTINGS_H
#define DTKPLOTVIEWSETTINGS_H

#include "dtkPlotExport.h"

#include <QtGui/QFrame>

class dtkPlotView;
class dtkPlotViewSettingsPrivate;

class DTKPLOT_EXPORT dtkPlotViewSettings : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(int width READ width WRITE setWidth)

public:
     dtkPlotViewSettings(dtkPlotView *parent);
    ~dtkPlotViewSettings(void);

     int width(void) const;

public:
    void update(void);

protected:
    void updateCurves(void);

public slots:
    void onShow(bool show);

     void setWidth(int width);

protected slots:
    void onMainTitleChanged(void);
    void onAxisTitleXChanged(void);
    void onAxisTitleYChanged(void);
    void onTitleSizeChanged(const int& value);
    void onAxesTitleSizeChanged(const int& value);
    void onLegendPositionChanged(const int& index);
    void onGridColorChanged(const QColor& color);
    void onZoomColorChanged(const QColor& color);
    void onBackgroundColorChanged(const QColor& color);
    void onForegroundColorChanged(const QColor& color);
    void onRandomColorsClicked(void);
    void onColorAreaChanged(const int& value);

    void updateCurveName(int);
    void updateCurveColor(int);

private:
    dtkPlotViewSettingsPrivate *d;
};

#endif
