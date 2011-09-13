/* dtkTextEditor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:23:52 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 10:52:10 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 57
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKTEXTEDITOR_H
#define DTKTEXTEDITOR_H

#include "dtkGuiExport.h"

#include <QtGui/QPlainTextEdit>
#include <QtGui/QWidget>

class dtkTextEditorPreferencesWidget;
class dtkTextEditorPrivate;

// /////////////////////////////////////////////////////////////////
// dtkTextEditorDocumentLayout
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkTextEditorDocumentLayout : public QPlainTextDocumentLayout
{
    Q_OBJECT

public:
    dtkTextEditorDocumentLayout(QTextDocument *document) : QPlainTextDocumentLayout(document) {
        lastSaveRevision = 0;
    }

    ~dtkTextEditorDocumentLayout(void) {

    }

public:
    int lastSaveRevision;
};

// /////////////////////////////////////////////////////////////////
// dtkTextEditorDocument
// /////////////////////////////////////////////////////////////////

class dtkTextEditorDocumentPrivate;

class DTKGUI_EXPORT dtkTextEditorDocument : public QObject
{
    Q_OBJECT

public:
     dtkTextEditorDocument(void);
    ~dtkTextEditorDocument(void);
    
    bool open (const QString& fileName);
    bool save (const QString& fileName = QString());
    bool close(void);

    bool isReadOnly(void) const;
    bool isModified(void) const;

    bool hasDecodingError(void);

    QString fileName(void) const;

    QTextDocument *document(void);

signals:
    void titleChanged(QString);
    void changed(void);

private:
    dtkTextEditorDocumentPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkTextEditor
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkTextEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
     dtkTextEditor(QWidget *parent = 0);
    ~dtkTextEditor(void);

    int currentLineNumber(void) const;
    int currentColumnNumber(void) const;

    bool isReadOnly(void) const;
    bool isModified(void) const;

    bool showLineNumbers(void);
    bool showCurrentLine(void);
    bool showRevisions(void);

    QString fileName(void) const;
    QString currentLine(void) const;

    int  backgroundOpacity(void) const;
    QColor backgroundColor(void) const;
    QColor foregroundColor(void) const;

    dtkTextEditorPreferencesWidget *preferencesWidget(QWidget *parent = 0);

    void setShowLineNumbers(bool show);
    void setShowCurrentLine(bool show);
    void setShowRevisions(bool show);

    void setBackgroundOpacity(int opacity);
    void setBackgroundColor(QColor color);
    void setForegroundColor(QColor color);

signals:
    void titleChanged(QString);
    void documentChanged(void);
    void closed(void);

public slots:
    bool open(const QString& fileName);
    bool save(const QString& fileName = QString());

    bool close(void);

    void  readSettings(void);
    void writeSettings(void);

    void zoomIn(int range = 1);
    void zoomOut(int range = 1);

protected:
    void closeEvent(QCloseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void changeEvent(QEvent *event);
    void focusInEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
#if defined(Q_WS_MAC)
    bool macEvent(EventHandlerCallRef caller, EventRef event);
#endif

protected:
    friend class dtkTextEditorExtraArea;

protected:
    int  extraAreaWidth(void) const;
    void extraAreaPaintEvent(QPaintEvent *event);

protected slots:
    void onBlockCountChanged(int);
    void onModificationChanged(bool);
    void onUpdateExtraAreaWidth(void);
    void onCursorPositionChanged(void);
    void onUpdateRequest(const QRect&, int);

private:
    QString textUnderCursor(void) const;

private:
    dtkTextEditorPrivate *d;
};

#endif // DTKTEXTEDITOR_H
