/* dtkInspector.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 31 11:07:21 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 16 22:09:53 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINSPECTOR_H
#define DTKINSPECTOR_H

#include <QtGui/QDialog>

#include "dtkGuiExport.h"

class dtkInspectorPrivate;

class DTKGUI_EXPORT dtkInspector : public QDialog
{
    Q_OBJECT

public:
     dtkInspector(QWidget *parent = 0);
    ~dtkInspector(void);

    QAction *addPage(const QString& title, QWidget *page);
    QAction *addPage(const QString& title, QWidget *page, const QIcon& icon);

public slots:
    void setTitle(const QString& title);

signals:
    void visibilityChanged(bool);

protected:
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void onActionTriggered(void);

private:
    dtkInspectorPrivate *d;
};

#endif
