/* dtkPlotView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:02:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 14:30:00 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 45
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

#include <dtkCore/dtkAbstractView.h>

#include <QtCore>
#include <QtGui>

class dtkPlotCurve;
class dtkPlotViewPrivate;

class DTKPLOT_EXPORT dtkPlotView : public dtkAbstractView
{
    Q_OBJECT

public:
     dtkPlotView(void);
    ~dtkPlotView(void);

    enum Scale {
        Linear,
        Logarithmic
    };

    void setAxisTitleX(const QString& title);
    void setAxisTitleY(const QString& title);
    
    void setAxisScaleX(double min, double max);
    void setAxisScaleY(double min, double max);

    void setAxisScaleX(Scale scale);
    void setAxisScaleY(Scale scale);

    void setBackgroundColor(const QColor& color);

    void setStyleSheet(const QString& sheet);

    dtkPlotView& operator<<(dtkPlotCurve *curve);

public slots:
    void update(void);

public slots:
    QWidget *widget(void);

private:
    friend class dtkPlotCurve;
    friend class dtkPlotRenderer;

private:
    dtkPlotViewPrivate *d;
};

#endif
