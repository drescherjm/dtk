/* dtkPlotViewToolBar.h --- 
 * 
 * Author: Selim Kraria
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 20 13:17:31 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 71
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEWTOOLBAR_H
#define DTKPLOTVIEWTOOLBAR_H

#include "dtkPlotExport.h"

#include <QtGui/QToolBar>

class dtkPlotView;
class dtkPlotViewToolBarPrivate;

class DTKPLOT_EXPORT dtkPlotViewToolBar : public QToolBar
{
    Q_OBJECT

public:
     dtkPlotViewToolBar(dtkPlotView *parent);
    ~dtkPlotViewToolBar(void);

protected:
    void onExport(const QString& file);

signals:
    void settingsClicked(bool value);

protected slots:
    void onExport(void);
    void onGridActivated(bool value);
    void onLegendActivated(bool value);
    void onPickingActivated(bool value);
    void onZoomActivated(bool value);

private:
    dtkPlotViewToolBarPrivate *d;
};

#endif
