/* dtkSpacer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct  7 09:21:29 2008 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 14 22:27:40 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSPACER_H
#define DTKSPACER_H

#include <QWidget>

#include "dtkGuiExport.h"

class DTKGUI_EXPORT dtkSpacer : public QWidget
{
    Q_OBJECT

public:
    dtkSpacer(QWidget *parent = 0, int width = 0, int height = 0);
   ~dtkSpacer(void);
    
    QSize sizeHint (void) const;
};

#endif
