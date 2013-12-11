/* dtkPlotViewLegend_p.h ---
 * 
 * Author: Julien Wintz
 * Created: Tue Oct  1 06:17:40 2013 (+0200)
 */

/* Change Log:
 * 
 */

#ifndef DTKPLOTVIEWLEGEND_P_H
#define DTKPLOTVIEWLEGEND_P_H

#include <dtkPlotExport.h>

#include <QtCore>

#include <qwt_legend.h>

class dtkPlotView;

class QwtPlot;
class QwtPlotItem;

class DTKPLOT_EXPORT dtkPlotViewLegendPrivate : public QwtLegend
{
    Q_OBJECT

public:
    dtkPlotViewLegendPrivate(dtkPlotView *parent);
    ~dtkPlotViewLegendPrivate(void);

protected slots:
#if QWT_VERSION >= 0x060100
    void legendChecked(const QVariant& itemInfo, bool value);
#endif
    void showCurve(QwtPlotItem *item, bool value);

public:
     dtkPlotView *plotView;
     QwtPlot *plot;
};

#endif
