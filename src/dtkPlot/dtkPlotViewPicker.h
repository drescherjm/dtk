/* dtkPlotViewPicker.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Jun 10 01:13:02 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Jun 10 01:13:27 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
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

private:
    dtkPlotViewPickerPrivate *d;
};

#endif
