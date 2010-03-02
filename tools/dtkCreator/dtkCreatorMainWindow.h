/* dtkCreatorMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:38:47 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Mar  2 10:11:39 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 28
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

class dtkAbstractData;
class dtkAbstractProcess;
class dtkAbstractView;
class dtkInterpreter;
class dtkScriptInterpreter;
class dtkCreatorMainWindowPrivate;

class dtkCreatorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     dtkCreatorMainWindow(QWidget *parent = 0);
    ~dtkCreatorMainWindow(void);

    void readSettings(void);
    void writeSettings(void);

    void interpret(const QString& file);

public slots:
    bool fileOpen(void);
    bool fileSave(void);
    bool fileSaveAs(void);

    void showInspector(void);
    void showPreferences(void);

    void onTitleChanged(QString title);
    void onDocumentChanged(void);

    void switchToEditor(void);
    void switchToComposer(void);
    void switchToViewer(void);

protected slots:
    void run(void);
    void stop(void);

    void registerData(dtkAbstractData *data, QString type);
    void registerProcess(dtkAbstractProcess *process, QString type);
    void registerView(dtkAbstractView *view, QString type);

protected:
    void closeEvent(QCloseEvent *event);

private:
    dtkCreatorMainWindowPrivate *d;
};

#endif
