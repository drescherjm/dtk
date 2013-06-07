/* dtkPlotViewLegend.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Jun 10 01:03:46 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 64
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotView.h"
#include "dtkPlotViewLegend.h"

#include <qwt_plot.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_item.h>

class dtkPlotViewLegendPrivate : public QwtLegend
{
public:
     dtkPlotViewLegendPrivate(QwtPlot *plot);
    ~dtkPlotViewLegendPrivate(void);

public:
     dtkPlotView *plotView;
};

dtkPlotViewLegendPrivate::dtkPlotViewLegendPrivate(QwtPlot *plot) : QwtLegend()
{
    setItemMode(QwtLegend::CheckableItem);

    plot->insertLegend(this);
}

dtkPlotViewLegendPrivate::~dtkPlotViewLegendPrivate(void)
{

}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkPlotViewLegend::dtkPlotViewLegend(dtkPlotView *parent) : QObject(parent), d(new dtkPlotViewLegendPrivate(reinterpret_cast<QwtPlot *>(parent->widget())))
{
    d->plotView = parent;

    QwtPlot *plot = reinterpret_cast<QwtPlot *>(parent->widget());

    QwtPlotItemList items = plot->itemList();
    for ( int i = 0; i < items.size(); i++ ) {
        QwtLegendItem *legendItem = (QwtLegendItem *)d->find(items[i]);
        if (legendItem) {
            if (items[i]->isVisible()) {
                legendItem->setChecked(true);
            }
        }
     }

    connect(plot, SIGNAL(legendChecked(QwtPlotItem *, bool)), this, SLOT(showItem(QwtPlotItem *, bool)));
}

dtkPlotViewLegend::~dtkPlotViewLegend(void)
{
    delete d;

    d = NULL;
}

void dtkPlotViewLegend::activate(void)
{
    d->setVisible(true);
}

void dtkPlotViewLegend::deactivate(void)
{
    d->setVisible(false);
}

void dtkPlotViewLegend::showItem(QwtPlotItem *item, bool value)
{
    item->setVisible(value);

    d->plotView->updateAxes();
}



