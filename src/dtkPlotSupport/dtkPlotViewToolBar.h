/* dtkPlotViewToolBar.h --- 
 * 
 * Author: Selim Kraria
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:54:01 2014 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 80
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

#include <QtWidgets>

class dtkPlotView;
class dtkPlotViewToolBarPrivate;

class DTKPLOT_EXPORT dtkPlotViewToolBar : public QFrame
{
    Q_OBJECT

public:
     dtkPlotViewToolBar(dtkPlotView *parent);
    ~dtkPlotViewToolBar(void);

protected:
    void onExport(const QString& file);

signals:
    void settingsClicked(bool value);

public:
    void setDark(bool dark);

protected slots:
    void onDefaultView(void);
    void onExport(void);
    void onGridActivated(bool value);
    void onLegendActivated(bool value);
    void onPickingActivated(bool value);
    void onZoomActivated(bool value);

private:
    dtkPlotViewToolBarPrivate *d;
};

#endif
