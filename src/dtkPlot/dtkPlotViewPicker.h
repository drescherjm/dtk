/* dtkPlotViewPicker.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Jun 10 01:13:02 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jun 24 12:38:06 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEWPICKER_H
#define DTKPLOTVIEWPICKER_H

#include "dtkPlotExport.h"

#include <QtCore/QObject>
#include <QtGui/QColor>

class dtkPlotView;
class dtkPlotViewPickerPrivate;

class DTKPLOT_EXPORT dtkPlotViewPicker : public QObject
{
    Q_OBJECT

public:
     dtkPlotViewPicker(dtkPlotView *parent);
    ~dtkPlotViewPicker(void);

public:
    void   activate(void);
    void deactivate(void);

public:
    QColor color(void) const;

    void setColor(const QColor& color);

private:
    dtkPlotViewPickerPrivate *d;
};

#endif
