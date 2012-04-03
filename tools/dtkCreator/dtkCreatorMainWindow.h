/* dtkCreatorMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:38:47 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:24:34 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 61
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCREATORMAINWINDOW_H
#define DTKCREATORMAINWINDOW_H

#include <dtkComposer/dtkComposerWriter.h>

#include <QtGui>

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
    bool compositionOpen(void);
    bool compositionOpen(const QString& file);
    bool compositionSave(void);
    bool compositionSaveAs(void);
    bool compositionSaveAs(const QString& file, dtkComposerWriter::Type type = dtkComposerWriter::Ascii);
    bool compositionInsert(void);
    bool compositionInsert(const QString& file);

protected slots:
    void switchToCompo(void);
    void switchToDstrb(void);
    void switchToDebug(void);

protected slots:
    void onConnect(void);

protected:
    void closeEvent(QCloseEvent *event);

private:
    dtkCreatorMainWindowPrivate *d;
};

#endif
