/* dtkInspector.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 23:26:46 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Aug  7 00:20:59 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINSPECTOR_H
#define DTKINSPECTOR_H

#include <QtGui/QMainWindow>

class dtkInspectorPrivate;

class dtkInspector : public QMainWindow
{
    Q_OBJECT

public:
     dtkInspector(QWidget *parent = 0);
    ~dtkInspector(void);

    void addPage(const QString& title, QWidget *page);
    void addPage(const QString& title, QWidget *page, const QIcon& icon);

private slots:
    void onActionHovered(void);
    void onActionTriggered(void);

private:
    dtkInspectorPrivate *d;
};

#endif
