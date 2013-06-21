/* dtkPlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:04:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun 21 15:31:41 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 335
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotCurve.h"
#include "dtkPlotView.h"
#include "dtkPlotViewPanner.h"
#include "dtkPlotViewPicker.h"
#include "dtkPlotViewZoomer.h"
#include "dtkPlotViewGrid.h"

#include "dtkPlotViewSettings.h"
#include "dtkPlotViewToolBar.h"

#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_widget.h>

#include <float.h>

class dtkPlotViewPrivate : public QwtPlot
{
public:
    dtkPlotViewPanner *panner;
    dtkPlotViewPicker *picker;
    dtkPlotViewZoomer *zoomer;
    dtkPlotViewGrid *grid;
    dtkPlotViewLegend *legend;

public:
    dtkPlotViewSettings *settings;
    dtkPlotViewToolBar *toolbar;

public:
    QFrame *frame_view;

public:
    QColor backgroundColor;
    QColor foregroundColor;

public:
    QList<dtkPlotCurve *> curves;
};

dtkPlotView::dtkPlotView(void) : dtkAbstractView(), d(new dtkPlotViewPrivate())
{
    d->panner = NULL;
    d->picker = NULL;
    d->zoomer = NULL;
    d->grid = NULL;
    d->legend = NULL;

    d->setAxisAutoScale(0, true);
    d->setAxisAutoScale(1, true);

    d->canvas()->setFrameStyle(QFrame::NoFrame);

    // Settings

    d->settings = new dtkPlotViewSettings(this);
    d->settings->setFixedWidth(0);

    // Tool bar

    d->toolbar = new dtkPlotViewToolBar(this);

    // Layout

    QFrame *frame = new QFrame;

    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d);
    layout->addWidget(d->toolbar);

    d->frame_view = new QFrame;

    QHBoxLayout *main_layout = new QHBoxLayout(d->frame_view);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(0);
    main_layout->addWidget(d->settings);
    main_layout->addWidget(frame);

    // Behaviour

    connect(d->toolbar, SIGNAL(settingsClicked(bool)), d->settings, SLOT(onShow(bool)));

    // General

    this->setStyleSheet(dtkReadFile(":dtkPlot/dtkPlotView.qss"));
    this->setBackgroundColor(Qt::white);
    this->setForegroundColor(Qt::black);
}

dtkPlotView::~dtkPlotView(void)
{
    delete d;

    d = NULL;
}

void dtkPlotView::clear(void)
{
    d->curves.clear();

    foreach (QwtPlotItem *item, d->itemList()) {
        item->detach();
    }

    this->update();
}

QList<dtkPlotCurve *> dtkPlotView::curves(void)
{
    return d->curves;
}

void dtkPlotView::activatePanning(void)
{
    if(!d->panner)
        d->panner = new dtkPlotViewPanner(this);

    d->panner->activate();
}

void dtkPlotView::updateAxes()
{
    qreal xmin = DBL_MAX;
    qreal xmax = DBL_MIN;
    qreal ymin = DBL_MAX;
    qreal ymax = DBL_MIN;

    foreach(dtkPlotCurve *curve, d->curves) {
      if (((QwtPlotCurve *)(curve->d))->isVisible()) {
        xmin = qMin(xmin, curve->minX());
        xmax = qMax(xmax, curve->maxX());
	ymin = qMin(ymin, curve->minY());
	ymax = qMax(ymax, curve->maxY());
      }
    }

    if (xmin < xmax) {
        this->setAxisScaleX(xmin, xmax);
        this->setAxisScaleY(ymin, ymax);
    }

    d->updateAxes();

    if(d->zoomer)
        d->zoomer->updateBase(QRectF(xmin, xmax, ymin, ymax));

    this->update();
}

void dtkPlotView::deactivatePanning(void)
{
    if(!d->panner)
        d->panner = new dtkPlotViewPanner(this);

    d->panner->deactivate();
}

void dtkPlotView::activatePicking(void)
{
    if(!d->picker)
        d->picker = new dtkPlotViewPicker(this);

    d->picker->activate();
}

void dtkPlotView::deactivatePicking(void)
{
    if(!d->picker)
        d->picker = new dtkPlotViewPicker(this);

    d->picker->deactivate();
}

void dtkPlotView::activateZooming(void)
{
    if(!d->zoomer)
        d->zoomer = new dtkPlotViewZoomer(this);

    d->zoomer->activate();
}

void dtkPlotView::deactivateZooming(void)
{
    if(!d->zoomer)
        d->zoomer = new dtkPlotViewZoomer(this);

    d->zoomer->deactivate();
}

void dtkPlotView::setZoomColor(const QColor& color)
{
    if(d->zoomer)
        d->zoomer->setColor(color);
}

void dtkPlotView::zoomForward(void)
{
    if(!d->zoomer)
        d->zoomer = new dtkPlotViewZoomer(this);

    d->zoomer->zoomForward();
}

void dtkPlotView::zoomBackward(void)
{
    d->zoomer->zoomBackward();
}

void dtkPlotView::activateGrid(void)
{
    if(!d->grid)
        d->grid = new dtkPlotViewGrid(this);

    d->grid->activate();

    this->update();
}

void dtkPlotView::deactivateGrid(void)
{
    if(!d->grid)
        d->grid = new dtkPlotViewGrid(this);

    d->grid->deactivate();

    this->update();
}

void dtkPlotView::setGridColor(const QColor& color)
{
    if(d->grid)
        d->grid->setColor(color);
}

void dtkPlotView::activateLegend(void)
{
    if(!d->legend)
        d->legend = new dtkPlotViewLegend(this);

    this->update();
}

void dtkPlotView::deactivateLegend(void)
{
    if(d->legend) {
      delete d->legend;
      d->legend = NULL;
      d->updateLayout();
    }

    this->update();
}

void dtkPlotView::setTitle(const QString& title)
{
    d->setTitle(title);
}

void dtkPlotView::setTitleSize(const int& size)
{
    QFont font;
    font.setFamily("verdana");
    font.setBold(false);
    font.setPointSize(size);

    QwtText title = d->title();
    title.setFont(font);

    d->setTitle(title);
}

QString dtkPlotView::title(void) const
{
    return d->title().text();
}

int dtkPlotView::titleSize(void) const
{
    return d->title().font().pointSize();
}

void dtkPlotView::setAxisTitleX(const QString& title)
{
    d->setAxisTitle(QwtPlot::xBottom, title);
}

QString dtkPlotView::axisTitleX(void) const
{
    return d->axisWidget(QwtPlot::xBottom)->title().text();
}

void dtkPlotView::setAxisTitleY(const QString& title)
{
    d->setAxisTitle(QwtPlot::yLeft, title);
}

QString dtkPlotView::axisTitleY(void) const
{
    return d->axisWidget(QwtPlot::yLeft)->title().text();
}

void dtkPlotView::setAxisTitleSizeX(const int& size)
{
    int axisId = QwtPlot::xBottom;

    QFont font = d->title().font();
    font.setPointSize(size);

    QwtText title = d->axisTitle(axisId);
    title.setFont(font);

    d->setAxisTitle(axisId, title);
}

void dtkPlotView::setAxisTitleSizeY(const int& size)
{
    int axisId = QwtPlot::yLeft;

    QFont font = d->title().font();
    font.setPointSize(size);

    QwtText title = d->axisTitle(axisId);
    title.setFont(font);

    d->setAxisTitle(axisId, title);
}

int dtkPlotView::axisTitleSizeX(void) const
{
    return d->axisWidget(QwtPlot::xBottom)->title().font().pointSize();
}

int dtkPlotView::axisTitleSizeY(void) const
{
    return d->axisWidget(QwtPlot::yLeft)->title().font().pointSize();
}

void dtkPlotView::setAxisScaleX(double min, double max)
{
    d->setAxisScale(QwtPlot::xBottom, min, max);
}

void dtkPlotView::setAxisScaleY(double min, double max)
{
    d->setAxisScale(QwtPlot::yLeft, min, max);
}

void dtkPlotView::setAxisScaleX(dtkPlotView::Scale scale)
{
    if(scale == dtkPlotView::Linear)
        d->setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine);
    
    if(scale == dtkPlotView::Logarithmic)
        d->setAxisScaleEngine(QwtPlot::xBottom, new QwtLog10ScaleEngine);
}

void dtkPlotView::setAxisScaleY(dtkPlotView::Scale scale)
{
    if(scale == dtkPlotView::Linear)
        d->setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine);
    
    if(scale == dtkPlotView::Logarithmic)
        d->setAxisScaleEngine(QwtPlot::yLeft, new QwtLog10ScaleEngine);
}

void dtkPlotView::setLegendPosition(LegendPosition position)
{
    if (d->legend) {
        d->legend->setPosition(position);
    }
}

void dtkPlotView::setBackgroundColor(int red, int green, int blue)
{
    this->setBackgroundColor(QColor(red, green, blue));
}

void dtkPlotView::setBackgroundColor(double red, double green, double blue)
{
    this->setBackgroundColor(QColor(red, green, blue));
}

void dtkPlotView::setBackgroundColor(const QColor& color)
{
    d->backgroundColor = color;

    d->setCanvasBackground(color);

    this->updateColors();
}

QColor dtkPlotView::backgroundColor() const
{
    return d->canvasBackground().color();
}

void dtkPlotView::setForegroundColor(const QColor& color)
{
    d->foregroundColor = color;

    this->updateColors();
}

QColor dtkPlotView::foregroundColor() const
{
    return d->foregroundColor;
}

void dtkPlotView::updateColors(void)
{
    QString sheet = "background: " + d->backgroundColor.name() + "; color: " + d->foregroundColor.name() + ";";

    d->setStyleSheet(sheet);

    this->update();
}

void dtkPlotView::fillCurveArea(int alpha)
{
    if (alpha < 0) {
        alpha = 0;
    } else if (alpha > 255) {
        alpha = 255;
    }

    foreach (dtkPlotCurve *curve, d->curves) {
        QColor color = curve->color();
        color.setAlphaF(alpha/255.);
        curve->setColorArea(color);
    }

    this->update();
}

void dtkPlotView::setStyleSheet(const QString& sheet)
{
    d->setStyleSheet(sheet);
    d->settings->setStyleSheet(sheet);
    d->toolbar->setStyleSheet(sheet);
}

dtkPlotView& dtkPlotView::operator<<(dtkPlotCurve *curve)
{
    QwtPlotCurve *c = ((QwtPlotCurve *)(curve->d));

    if (c->plot() != d)
        d->curves << curve;

    if (c->plot() != d)
        c->attach((QwtPlot *)d);

    return *(this);
}

void dtkPlotView::update(void)
{
    d->replot();

    d->settings->update();
}

QWidget *dtkPlotView::widget(void)
{
    return d->frame_view;
}

QWidget *dtkPlotView::plotWidget(void)
{
    return d;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkAbstractView *createPlotView(void)
{
    return new dtkPlotView;
}
