/* dtkInspector.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 23:26:46 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Mar 14 15:03:59 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINSPECTOR_H
#define DTKINSPECTOR_H

#include "dtkGuiExport.h"

#include <QtGui/QMainWindow>

class dtkInspectorPrivate;

class DTKGUI_EXPORT dtkInspector : public QMainWindow
{
    Q_OBJECT

public:
     dtkInspector(QWidget *parent = 0);
    ~dtkInspector(void);

    void readSettings(void);
    void writeSettings(void);

    QAction *addPage(const QString& title, QWidget *page);
    QAction *addPage(const QString& title, QWidget *page, const QIcon& icon);

private slots:
    void onActionTriggered(void);

private:
    dtkInspectorPrivate *d;
};

#endif
