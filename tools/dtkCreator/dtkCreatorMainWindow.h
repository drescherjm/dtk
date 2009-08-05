/* dtkCreatorMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:38:47 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Aug  5 12:55:18 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCREATORMAINWINDOW_H
#define DTKCREATORMAINWINDOW_H

#include <QtGui/QMainWindow>

class dtkInterpreter;

class dtkCreatorMainWindowPrivate;

class dtkCreatorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     dtkCreatorMainWindow(QWidget *parent = 0);
    ~dtkCreatorMainWindow(void);

    void readSettings(void);
    void writeSettings(void);

public slots:
    bool fileOpen(void);
    bool fileSave(void);
    bool fileSaveAs(void);

    void showPreferences(void);

    void onTitleChanged(QString title);
    void onDocumentChanged(void);

    void switchToTextualEditor(void);
    void switchToVisualEditor(void);
    void switchToViewer(void);

protected:
    void closeEvent(QCloseEvent *event);

private:
    dtkCreatorMainWindowPrivate *d;
};

#endif
