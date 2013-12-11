/* dtkPlotViewLegend_p.h ---
 * 
 * Author: Julien Wintz
 * Created: Tue Oct  1 06:17:40 2013 (+0200)
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkPlotExport.h>

#include "dtkPlotView.h"

#include <QtCore>

#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_plot_item.h>

class dtkPlotViewLegendPrivate : public QwtLegend
{
    Q_OBJECT

public:
    dtkPlotViewLegendPrivate(dtkPlotView *parent) {
#if QWT_VERSION >= 0x060100
        setDefaultItemMode(QwtLegendData::Checkable);
#else
        setItemMode(QwtLegend::CheckableItem);
#endif

        plot = reinterpret_cast<QwtPlot *>(parent->plotWidget());
        plot->insertLegend(this, QwtPlot::RightLegend);
    };
    ~dtkPlotViewLegendPrivate(void) {};

protected slots:
#if QWT_VERSION >= 0x060100
    void legendChecked(const QVariant& itemInfo, bool value) {
        QwtPlotItem *plotItem = plot->infoToItem(itemInfo);
        if (plotItem) {
            this->showCurve(plotItem, value);
        }
    };
#endif
    void showCurve(QwtPlotItem *item, bool value) {
        item->setVisible(value);
        plotView->updateAxes();
    };

public:
     dtkPlotView *plotView;
     QwtPlot *plot;
};
