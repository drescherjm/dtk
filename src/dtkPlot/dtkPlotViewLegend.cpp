/* dtkPlotViewLegend.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 25 14:23:59 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 137
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotView.h"
#include "dtkPlotViewLegend.h"

#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#if QWT_VERSION >= 0x060100
#include <qwt_legend_label.h>
#else
#include <qwt_legend_item.h>
#endif
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
#if QWT_VERSION >= 0x060100
    setDefaultItemMode(QwtLegendData::Checkable);
#else
    setItemMode(QwtLegend::CheckableItem);
#endif

    plot = reinterpret_cast<QwtPlot *>(parent->plotWidget());

    plot->insertLegend(this, QwtPlot::RightLegend);
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
#if QWT_VERSION >= 0x060100
        QList<QWidget *> legendWidgets = d->legendWidgets(d->plot->itemToInfo(items[i]));
        if (legendWidgets.size() == 1 ) {
            QwtLegendLabel *legendLabel = qobject_cast<QwtLegendLabel *>(legendWidgets[0]);
            if (legendLabel) {
                legendLabel->setChecked(true);
            }
        }
#else
        QwtLegendItem *legendItem = (QwtLegendItem *)d->find(items[i]);
        if (legendItem) {
            if (items[i]->isVisible()) {
                legendItem->setChecked(true);
            }
        }
#endif
     }

#if QWT_VERSION >= 0x060100
    connect(d, SIGNAL(checked(const QVariant&, bool, int)), this, SLOT(legendChecked(const QVariant&, bool)));
#else
    connect(d->plot, SIGNAL(legendChecked(QwtPlotItem *, bool)), this, SLOT(showCurve(QwtPlotItem *, bool)));
#endif
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

    d->plotView->update();
}

#if QWT_VERSION >= 0x060100
void dtkPlotViewLegend::legendChecked(const QVariant &itemInfo, bool value)
{
    QwtPlotItem *plotItem = d->plot->infoToItem(itemInfo);
    if (plotItem) {
        this->showCurve(plotItem, value);
    }
}
#endif

void dtkPlotViewLegend::showCurve(QwtPlotItem *item, bool value)
{
    item->setVisible(value);

    d->plotView->updateAxes();
}


