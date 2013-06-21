/* dtkPlotViewLegend.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 20 15:56:27 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 99
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
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_item.h>

class dtkPlotViewLegendPrivate : public QwtLegend
{
public:
     dtkPlotViewLegendPrivate(dtkPlotView *parent);
    ~dtkPlotViewLegendPrivate(void);

public:
     dtkPlotView *plotView;
     QwtPlot *plot;
};

dtkPlotViewLegendPrivate::dtkPlotViewLegendPrivate(dtkPlotView *parent) : QwtLegend()
{
    setItemMode(QwtLegend::CheckableItem);

    plot = reinterpret_cast<QwtPlot *>(parent->plotWidget());

    plot->insertLegend(this, QwtPlot::LeftLegend);
}

dtkPlotViewLegendPrivate::~dtkPlotViewLegendPrivate(void)
{

}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkPlotViewLegend::dtkPlotViewLegend(dtkPlotView *parent) : QObject(parent), d(new dtkPlotViewLegendPrivate(parent))
{
    d->plotView = parent;

    QwtPlotItemList items = d->plot->itemList();
    for ( int i = 0; i < items.size(); i++ ) {
        QwtLegendItem *legendItem = (QwtLegendItem *)d->find(items[i]);
        if (legendItem) {
            if (items[i]->isVisible()) {
                legendItem->setChecked(true);
            }
        }
     }

    connect(d->plot, SIGNAL(legendChecked(QwtPlotItem *, bool)), this, SLOT(showItem(QwtPlotItem *, bool)));
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

void dtkPlotViewLegend::setPosition(int position)
{
    QwtPlot::LegendPosition pos;

    switch (position) {
    case 0:
        pos = QwtPlot::LeftLegend;
        break;
    case 1:
        pos = QwtPlot::RightLegend;
        break;
    case 2:
        pos = QwtPlot::BottomLegend;
        break;
    default:
        pos = QwtPlot::TopLegend;
        break;
    }

    d->plot->plotLayout()->setLegendPosition(pos);

    d->plot->updateLayout();

    d->plotView->update();
}


