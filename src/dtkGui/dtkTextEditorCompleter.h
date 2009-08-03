/* dtkTextEditorCompleter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 17 09:14:41 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 14:54:10 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKTEXTEDITORCOMPLETER_H
#define DTKTEXTEDITORCOMPLETER_H

#include <QtGui>

#include <dtkCore/dtkGlobal.h>

#include "dtkGuiExport.h"

class dtkTextEditor;
class dtkTextEditorCompleterPrivate;

class DTKGUI_EXPORT dtkTextEditorCompleter : public QCompleter
{
    Q_OBJECT

public:
     dtkTextEditorCompleter(dtkTextEditor *parent = 0);
    ~dtkTextEditorCompleter(void);

public slots:
    virtual void update(void) {}

protected:
    dtkTextEditor *editor(void);

private:
    dtkTextEditorCompleterPrivate *d;
};

class dtkTextEditorCompleterDocumentPrivate;

class DTKGUI_EXPORT dtkTextEditorCompleterDocument : public dtkTextEditorCompleter
{
    Q_OBJECT

public:
     dtkTextEditorCompleterDocument(dtkTextEditor *parent = 0);
    ~dtkTextEditorCompleterDocument(void);

public slots:
    virtual void update(void);

private:
    dtkTextEditorCompleterDocumentPrivate *d;
};

class dtkTextEditorCompleterPathPrivate;

class DTKGUI_EXPORT dtkTextEditorCompleterPath : public dtkTextEditorCompleter
{
    Q_OBJECT

public:
     dtkTextEditorCompleterPath(dtkTextEditor *parent = 0);
    ~dtkTextEditorCompleterPath(void);

private:
    dtkTextEditorCompleterPathPrivate *d;
};

#endif
