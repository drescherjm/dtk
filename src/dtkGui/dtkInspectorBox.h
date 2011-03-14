/* dtkInspectorBox.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 31 12:19:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 15:05:40 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINSPECTORBOX_H
#define DTKINSPECTORBOX_H

#include <QtGui/QFrame>

#include "dtkGuiExport.h"

class dtkInspectorBoxPrivate;

class DTKGUI_EXPORT dtkInspectorBox : public QFrame
{
    Q_OBJECT

public:
     dtkInspectorBox(QWidget *parent = 0);
    ~dtkInspectorBox(void);

private:
    dtkInspectorBoxPrivate *d;
};

#endif
