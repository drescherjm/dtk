/* dtkPlotViewLegend.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotViewLegend.h"
#include "dtkPlotViewLegend_p.h"

#if QWT_VERSION >= 0x060100
#include <qwt_legend_label.h>
#else
#include <qwt_legend_item.h>
#endif

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
    connect(d, SIGNAL(checked(const QVariant&, bool, int)), d, SLOT(legendChecked(const QVariant&, bool)));
#else
    connect(d->plot, SIGNAL(legendChecked(QwtPlotItem *, bool)), d, SLOT(showCurve(QwtPlotItem *, bool)));
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
