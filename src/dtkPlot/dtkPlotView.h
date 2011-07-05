/* dtkPlotView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:02:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul  5 14:22:02 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 35
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

#include <QtCore>
#include <QtGui>

class dtkPlotCurve;
class dtkPlotViewPrivate;

class DTKPLOT_EXPORT dtkPlotView : public QWidget
{
    Q_OBJECT

public:
     dtkPlotView(QWidget *parent = 0);
    ~dtkPlotView(void);

    void setAxisTitleX(const QString& title);
    void setAxisTitleY(const QString& title);
    
    void setAxisScaleX(double min, double max);
    void setAxisScaleY(double min, double max);

    void setBackgroundColor(const QColor& color);

    dtkPlotView& operator<<(dtkPlotCurve *curve);

private:
    friend class dtkPlotCurve;
    friend class dtkPlotRenderer;

private:
    dtkPlotViewPrivate *d;
};

#endif
