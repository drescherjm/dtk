/* dtkTextEditorCompleter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 17 09:18:14 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 14:57:20 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 38
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkGui/dtkTextEditor.h>
#include <dtkGui/dtkTextEditorCompleter.h>

// /////////////////////////////////////////////////////////////////
// dtkTextEditorCompleter
// /////////////////////////////////////////////////////////////////

class dtkTextEditorCompleterPrivate
{
public:
    dtkTextEditor *editor;
};

dtkTextEditorCompleter::dtkTextEditorCompleter(dtkTextEditor *parent) : QCompleter(parent), d(new dtkTextEditorCompleterPrivate)
{
    d->editor = parent;
}

dtkTextEditorCompleter::~dtkTextEditorCompleter(void)
{
    delete d;

    d = NULL;
}

dtkTextEditor *dtkTextEditorCompleter::editor(void)
{
    return d->editor;
}

// /////////////////////////////////////////////////////////////////
// dtkTextEditorCompleterDocument
// /////////////////////////////////////////////////////////////////

class dtkTextEditorCompleterDocumentPrivate
{
public:
};

dtkTextEditorCompleterDocument::dtkTextEditorCompleterDocument(dtkTextEditor *parent) : dtkTextEditorCompleter(parent), d(new dtkTextEditorCompleterDocumentPrivate)
{
    this->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    this->setCaseSensitivity(Qt::CaseInsensitive);
    this->setWrapAround(false);

    connect(this->editor()->document(), SIGNAL(blockCountChanged(int)), this, SLOT(update()));
}

dtkTextEditorCompleterDocument::~dtkTextEditorCompleterDocument(void)
{
    delete d;

    d = NULL;
}

void dtkTextEditorCompleterDocument::update(void)
{
 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
 #endif
     QStringList words = this->editor()->toPlainText().split(QRegExp("\\W+"), QString::SkipEmptyParts);

 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     this->setModel(new QStringListModel(words, this));
}

// /////////////////////////////////////////////////////////////////
// dtkTextEditorCompleterPath
// /////////////////////////////////////////////////////////////////

class dtkTextEditorCompleterPathPrivate
{
public:
};

dtkTextEditorCompleterPath::dtkTextEditorCompleterPath(dtkTextEditor *parent) : dtkTextEditorCompleter(parent), d(new dtkTextEditorCompleterPathPrivate)
{
    this->setModel(new QDirModel(this));
    this->setCompletionMode(QCompleter::InlineCompletion);
}

dtkTextEditorCompleterPath::~dtkTextEditorCompleterPath(void)
{
    delete d;

    d = NULL;
}
