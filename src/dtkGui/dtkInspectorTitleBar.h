/* dtkInspectorTitleBar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 13 21:12:26 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 14:48:49 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINSPECTORTITLEBAR_H
#define DTKINSPECTORTITLEBAR_H

#include <QtGui/QWidget>

#include "dtkGuiExport.h"

class dtkInspectorTitleBarPrivate;

class DTKGUI_EXPORT dtkInspectorTitleBar : public QWidget
{
    Q_OBJECT

public:
     dtkInspectorTitleBar(QWidget *parent = 0);
    ~dtkInspectorTitleBar(void);

    QSize sizeHint(void) const;

    void setTitle(const QString& title);

signals:
    void closed(void);

protected:
    void paintEvent(QPaintEvent *event);

private:
    dtkInspectorTitleBarPrivate *d;
};

#endif
