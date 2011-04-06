/* dtkInspectorSwitch.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb  4 17:07:56 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 14:55:11 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINSPECTORSWITCH_H
#define DTKINSPECTORSWITCH_H

#include <QtGui/QWidget>

#include "dtkGuiExport.h"

class dtkInspectorSwitchPrivate;

class DTKGUI_EXPORT dtkInspectorSwitch : public QWidget
{
    Q_OBJECT

public:
     dtkInspectorSwitch(QWidget *parent = 0);
    ~dtkInspectorSwitch(void);

    QSize sizeHint(void) const;

signals:
    void toggled(bool);

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    dtkInspectorSwitchPrivate *d;
};

#endif
