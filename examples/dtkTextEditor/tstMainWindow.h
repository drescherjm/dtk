/* tstMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:19:37 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 14:29:41 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTMAINWINDOW_H
#define TSTMAINWINDOW_H

#include <QMainWindow>

class tstMainWindowPrivate;

class tstMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     tstMainWindow(QWidget *parent = 0);
    ~tstMainWindow(void);

public slots:
    bool fileOpen  (void);
    bool fileOpen  (const QString& file);
    bool fileSave  (void);
    bool fileSaveAs(void);

    void onTitleChanged(QString title);
    void onDocumentChanged(void);

protected:
    void closeEvent(QCloseEvent *event);

private:
    tstMainWindowPrivate *d;
};

#endif // TSTMAINWINDOW_H
