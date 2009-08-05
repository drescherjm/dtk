/* dtkTextEditor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:23:18 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Aug  5 11:14:59 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 117
 */

/* Commentary: 
 * See credits at end of file.
 */

/* Change log:
 * 
 */

#include <QtGui>

#include <dtkCore/dtkLog.h>

#include <dtkGui/dtkTextEditor.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterCpp.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterPython.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterTcl.h>
#include <dtkGui/dtkTextEditorPreferencesWidget.h>

class dtkTextEditorExtraArea : public QWidget
{
public:
    dtkTextEditorExtraArea(dtkTextEditor *editor) : QWidget(editor) {
        this->editor = editor;
        this->setAutoFillBackground(true);
    }

    QSize sizeHint(void) const {
        return QSize(editor->extraAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        editor->extraAreaPaintEvent(event);
    }

private:
    dtkTextEditor *editor;
};

// /////////////////////////////////////////////////////////////////
// dtkTextEditorDocumentPrivate
// /////////////////////////////////////////////////////////////////

class dtkTextEditorDocumentPrivate
{
public:
    enum LineTerminatorMode {
        LFLineTerminator,
        CRLFLineTerminator,
        NativeLineTerminator =
#if defined (Q_OS_WIN32)
        CRLFLineTerminator
#else
        LFLineTerminator
#endif
    };

public:
    bool isBinaryData;
    bool hasDecodingError;

    QString fileName;
    QTextCodec *codec;
    QTextDocument *document;
    QByteArray decodingErrorSample;

    LineTerminatorMode lineTerminatorMode;
};

// /////////////////////////////////////////////////////////////////
// dtkTextEditorDocument
// /////////////////////////////////////////////////////////////////

dtkTextEditorDocument::dtkTextEditorDocument(void)
{
    d = new dtkTextEditorDocumentPrivate;

    d->isBinaryData = false;
    d->hasDecodingError = false;
    d->lineTerminatorMode = dtkTextEditorDocumentPrivate::NativeLineTerminator;

    d->fileName = "untitled";
    d->codec = QTextCodec::codecForLocale();
    d->document = new QTextDocument(this);

    emit titleChanged(d->fileName);
}

dtkTextEditorDocument::~dtkTextEditorDocument(void)
{
    delete d->document;
    delete d;
}

bool dtkTextEditorDocument::open(const QString& fileName)
{
    if (!fileName.isEmpty()) {
        const QFileInfo fi(fileName);
        d->fileName = fi.absoluteFilePath();

        QFile file(fileName);
        if (!file.exists())
            return false;

        if (!fi.isReadable())
            return false;

        if (!fi.isWritable()) {
            if (!file.open(QIODevice::ReadOnly))
                return false;
        } else {
            if (!file.open(QIODevice::ReadWrite))
                return false;
        }
        QString title = fi.fileName();

        QByteArray buf = file.readAll();
        int bytesRead = buf.size();

        QTextCodec *codec = d->codec;

        if (bytesRead >= 4 && ((uchar(buf[0]) == 0xff && uchar(buf[1]) == 0xfe && uchar(buf[2]) == 0 && uchar(buf[3]) == 0)
                               || (uchar(buf[0]) == 0 && uchar(buf[1]) == 0 && uchar(buf[2]) == 0xfe && uchar(buf[3]) == 0xff))) {
            codec = QTextCodec::codecForName("UTF-32");
        } else if (bytesRead >= 2 && ((uchar(buf[0]) == 0xff && uchar(buf[1]) == 0xfe)
                                      || (uchar(buf[0]) == 0xfe && uchar(buf[1]) == 0xff))) {
            codec = QTextCodec::codecForName("UTF-16");
        } else if (!codec) {
            codec = QTextCodec::codecForLocale();
        }

        QString text = d->codec->toUnicode(buf);
        QByteArray verifyBuf = d->codec->fromUnicode(text);

        int minSize = qMin(verifyBuf.size(), buf.size());
        d->hasDecodingError = (minSize < buf.size()- 4
                               || memcmp(verifyBuf.constData() + verifyBuf.size() - minSize,
                                         buf.constData() + buf.size() - minSize, minSize));

        if (d->hasDecodingError) {
            int p = buf.indexOf('\n', 16384);
            if (p < 0)
                d->decodingErrorSample = buf;
            else
                d->decodingErrorSample = buf.left(p);
        } else {
            d->decodingErrorSample.clear();
        }

        int lf = text.indexOf('\n');
        if (lf > 0 && text.at(lf-1) == QLatin1Char('\r')) {
            d->lineTerminatorMode = dtkTextEditorDocumentPrivate::CRLFLineTerminator;
        } else if (lf >= 0) {
            d->lineTerminatorMode = dtkTextEditorDocumentPrivate::LFLineTerminator;
        } else {
            d->lineTerminatorMode = dtkTextEditorDocumentPrivate::NativeLineTerminator;
        }

        d->document->setModified(false);
        d->document->setUndoRedoEnabled(false);
        if (d->isBinaryData)
            d->document->setHtml(tr("<em>Binary data</em>"));
        else
            d->document->setPlainText(text);
        d->document->setUndoRedoEnabled(true);

        dtkTextEditorDocumentLayout *documentLayout = qobject_cast<dtkTextEditorDocumentLayout*>(d->document->documentLayout());
        documentLayout->lastSaveRevision = 0;
        d->document->setModified(false);

        emit titleChanged(title);
        emit changed();
    }

    return true;
}

bool dtkTextEditorDocument::save(const QString& fileName)
{
    QString fName = d->fileName;
    if (!fileName.isEmpty())
        fName = fileName;

    QFile file(fName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    QString plainText = d->document->toPlainText();

    if (d->lineTerminatorMode == dtkTextEditorDocumentPrivate::CRLFLineTerminator)
        plainText.replace(QLatin1Char('\n'), QLatin1String("\r\n"));

    file.write(d->codec->fromUnicode(plainText));
    if (!file.flush())
        return false;
    file.close();

    const QFileInfo fi(fName);
    d->fileName = fi.absoluteFilePath();

    d->document->setModified(false);
    emit titleChanged(fi.fileName());
    emit changed();

    d->isBinaryData = false;
    d->hasDecodingError = false;
    d->decodingErrorSample.clear();

    return true;
}

bool dtkTextEditorDocument::close(void)
{
    d->document->setPlainText("");

    dtkTextEditorDocumentLayout *documentLayout = qobject_cast<dtkTextEditorDocumentLayout*>(d->document->documentLayout());
    documentLayout->lastSaveRevision = 0;
    d->document->setModified(false);

    d->isBinaryData = false;
    d->hasDecodingError = false;
    d->decodingErrorSample.clear();

    emit titleChanged("untitled");
    emit changed();

    return true;
}

bool dtkTextEditorDocument::isReadOnly(void) const
{
    if (d->isBinaryData || d->hasDecodingError)
        return true;
    if (d->fileName.isEmpty())
        return false;
    const QFileInfo fi(d->fileName);
    return !fi.isWritable();
}

bool dtkTextEditorDocument::isModified(void) const
{
    return d->document->isModified();
}

bool dtkTextEditorDocument::hasDecodingError(void)
{
    return d->hasDecodingError;
}

QString dtkTextEditorDocument::fileName(void) const
{
    return d->fileName;
}

QTextDocument *dtkTextEditorDocument::document(void)
{
    return d->document;
}

// /////////////////////////////////////////////////////////////////
// dtkTextEditorPrivate
// /////////////////////////////////////////////////////////////////

class dtkTextEditorPrivate
{
public:
    bool showLineNumbers;
    bool showCurrentLine;
    bool showRevisions;

    dtkTextEditorDocument *document;

    dtkTextEditorExtraArea *extraArea;
    dtkTextEditorPreferencesWidget *preferences;
};

// /////////////////////////////////////////////////////////////////
// dtkTextEditorPrivate
// /////////////////////////////////////////////////////////////////

dtkTextEditor::dtkTextEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    d = new dtkTextEditorPrivate;
    d->showLineNumbers = true;
    d->showCurrentLine = true;
    d->showRevisions = true;

    d->extraArea = new dtkTextEditorExtraArea(this);
    d->preferences = NULL;

    d->document = new dtkTextEditorDocument;
    // begin setting up document
    QTextDocument *doc = d->document->document();
    dtkTextEditorDocumentLayout *documentLayout = qobject_cast<dtkTextEditorDocumentLayout*>(doc->documentLayout());
    if(!documentLayout) {
        documentLayout = new dtkTextEditorDocumentLayout(doc);
        doc->setDocumentLayout(documentLayout);
    }
    // end setting up document
    this->setDocument(doc);

    this->setAutoFillBackground(true);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setCursorWidth(2);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(onBlockCountChanged(int)));
    connect(this, SIGNAL(modificationChanged(bool)), this, SLOT(onModificationChanged(bool)));
    connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(onUpdateRequest(QRect, int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));

    connect(doc, SIGNAL(contentsChanged()), this, SIGNAL(documentChanged()));

    connect(d->document, SIGNAL(titleChanged(QString)), this, SIGNAL(titleChanged(QString)));

    this->onUpdateExtraAreaWidth();

    this->installEventFilter(this);
}

dtkTextEditor::~dtkTextEditor(void)
{
    delete d;
}

void dtkTextEditor::readSettings(void)
{    
    QSettings settings("inria", "dtk");
    settings.beginGroup("editor");
    this->setFont(settings.value("font").value<QFont>());
    this->setShowRevisions(settings.value("showRevisions").toBool());
    this->setShowCurrentLine(settings.value("showCurrentLine").toBool());
    this->setShowLineNumbers(settings.value("showLineNumbers").toBool());
    settings.endGroup();
}

void dtkTextEditor::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("editor");
    settings.setValue("font", this->font());
    settings.setValue("showRevisions", this->showRevisions());
    settings.setValue("showCurrentLine", this->showCurrentLine());
    settings.setValue("showLineNumbers", this->showLineNumbers());
    settings.endGroup();
}

int dtkTextEditor::currentLineNumber(void) const
{
    return this->textCursor().blockNumber() + 1;
}

int dtkTextEditor::currentColumnNumber(void) const
{
    return this->textCursor().position() - this->textCursor().block().position() + 1;
}

bool dtkTextEditor::open(const QString& fileName)
{
    if (d->document->open(fileName)) {
        moveCursor(QTextCursor::Start);
        setReadOnly(d->document->hasDecodingError());

        if(fileName.endsWith(".cpp") || fileName.endsWith(".cxx") || fileName.endsWith(".c") || fileName.endsWith(".h"))
            new dtkTextEditorSyntaxHighlighterCpp(this);

        if(fileName.endsWith(".py"))
            new dtkTextEditorSyntaxHighlighterPython(this);

        if(fileName.endsWith(".tcl"))
            new dtkTextEditorSyntaxHighlighterTcl(this);

        return true;
    }

    return false;
}

bool dtkTextEditor::save(const QString& fileName)
{    
    return d->document->save(fileName);
}

bool dtkTextEditor::close(void)
{
    return d->document->close();
}

bool dtkTextEditor::isReadOnly(void) const
{
    return d->document->isReadOnly();
}

bool dtkTextEditor::isModified(void) const
{
    return d->document->isModified();
}

bool dtkTextEditor::showLineNumbers(void)
{
    return d->showLineNumbers;
}

bool dtkTextEditor::showCurrentLine(void)
{
    return d->showCurrentLine;
}

bool dtkTextEditor::showRevisions(void)
{
    return d->showRevisions;
}

QString dtkTextEditor::fileName(void) const
{
    return d->document->fileName();
}

QString dtkTextEditor::currentLine(void) const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::LineUnderCursor);
    
    return tc.selectedText();
}

int dtkTextEditor::backgroundOpacity(void) const
{
    // return (int)(this->windowOpacity()*255);

    QPalette p(this->palette());
    return p.color(QPalette::Base).alpha();
}

QColor dtkTextEditor::backgroundColor(void) const
{
    QPalette p(palette());
    return p.color(QPalette::Base);
}

QColor dtkTextEditor::foregroundColor(void) const
{
    QPalette p(palette());
    return p.color(QPalette::Text);
}

dtkTextEditorPreferencesWidget *dtkTextEditor::preferencesWidget(QWidget *parent)
{
    if(!d->preferences)
        d->preferences = new dtkTextEditorPreferencesWidget(this, parent);

    return d->preferences;
}

void dtkTextEditor::setShowLineNumbers(bool show)
{
    d->showLineNumbers = show;

    onUpdateExtraAreaWidth();
}

void dtkTextEditor::setShowCurrentLine(bool show)
{
    d->showCurrentLine = show;
}

void dtkTextEditor::setShowRevisions(bool show)
{
    d->showRevisions = show;

    onUpdateExtraAreaWidth();
}

void dtkTextEditor::setBackgroundOpacity(int opacity)
{
    // this->setWindowOpacity((qreal)(opacity/255.0));

    QPalette p(this->palette());

    QColor color = p.color(QPalette::Base);
    color.setAlpha(opacity);
    p.setColor(QPalette::Window, color);

    this->setPalette(p);
    
    this->viewport()->update();
}

void dtkTextEditor::setBackgroundColor(QColor color)
{
    QPalette p(this->palette());
    p.setColor(QPalette::Base, color);

    this->setPalette(p);

    this->viewport()->update();
}

void dtkTextEditor::setForegroundColor(QColor color)
{
    QPalette p(this->palette());
    p.setColor(QPalette::Text, color);

    this->setPalette(p);

    this->viewport()->update();
}

void dtkTextEditor::changeEvent(QEvent *e)
{
    QPlainTextEdit::changeEvent(e);

    if (e->type() == QEvent::ApplicationFontChange || e->type() == QEvent::FontChange) {
        if (d->extraArea) {
            QFont f = d->extraArea->font();
            f.setPointSize(font().pointSize());
            d->extraArea->setFont(f);
            onUpdateExtraAreaWidth();
            d->extraArea->update();
        }
    }
}

void dtkTextEditor::focusInEvent(QFocusEvent *event)
{
    QPlainTextEdit::focusInEvent(event);
}

#include <iostream>

void dtkTextEditor::keyPressEvent(QKeyEvent *event)
{
    QPlainTextEdit::keyPressEvent(event);
}

void dtkTextEditor::paintEvent(QPaintEvent *event)
{
    const QColor baseColor = palette().base().color();

    const int blendBase   = (baseColor.value() > 128) ? 0 : 255;
    const int blendFactor = (baseColor.value() > 128) ? 8 : 16;

    const QColor blendColor(
        (blendBase * blendFactor + baseColor.blue()  * (256 - blendFactor)) / 256,
        (blendBase * blendFactor + baseColor.green() * (256 - blendFactor)) / 256,
        (blendBase * blendFactor + baseColor.blue()  * (256 - blendFactor)) / 256);

    QPainter painter(viewport());

    if(d->showCurrentLine) {
        QRect r = cursorRect();
        r.setX(0);
        r.setWidth(viewport()->width());
        painter.fillRect(r, blendColor);
    }

    painter.end();

    QPlainTextEdit::paintEvent(event);
}

void dtkTextEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = viewport()->rect();
    d->extraArea->setGeometry(QStyle::visualRect(layoutDirection(), cr, QRect(cr.left(), cr.top(), extraAreaWidth(), cr.height())));
}

void dtkTextEditor::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        const int delta = event->delta();
        if (delta < 0)
            zoomOut();
        else if (delta > 0)
            zoomIn();
        return;
    }

    QPlainTextEdit::wheelEvent(event);
}

bool dtkTextEditor::eventFilter(QObject *object, QEvent *event)
{
    dtkLogEvent *logEvent = dynamic_cast<dtkLogEvent *>(event);
    dtkTextEditor *editor = dynamic_cast<dtkTextEditor *>(object);

    if (logEvent && editor) {
        editor->appendPlainText(logEvent->message());
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}

void dtkTextEditor::zoomIn(int range)
{
    QFont f = font();
    const int newSize = f.pointSize() + range;
    if (newSize <= 0)
        return;
    f.setPointSize(newSize);
    setFont(f);
}

void dtkTextEditor::zoomOut(int range)
{
    zoomIn(-range);
}

int dtkTextEditor::extraAreaWidth(void) const
{
    if(!d->showLineNumbers && !d->showRevisions)
        return 0;

    dtkTextEditorDocumentLayout *documentLayout = qobject_cast<dtkTextEditorDocumentLayout *>(this->document()->documentLayout());

    if(!documentLayout)
        return 0;

    int space = 0;
    const QFontMetrics fm(d->extraArea->fontMetrics());

    if (d->showLineNumbers) {
        int digits = 2;
        int max = qMax(1, this->blockCount());
        while (max >= 100) {
            max /= 10;
            ++digits;
        }
        space += fm.width(QLatin1Char('9')) * digits;
    }

    space += 4;

    return space;
}

void dtkTextEditor::extraAreaPaintEvent(QPaintEvent *event)
{
    if(!d->showLineNumbers && !d->showRevisions)
        return;

    dtkTextEditorDocumentLayout *documentLayout = qobject_cast<dtkTextEditorDocumentLayout *>(this->document()->documentLayout());

    QPalette palette = d->extraArea->palette();
    palette.setCurrentColorGroup(QPalette::Active);

    QPainter painter(d->extraArea);

    QFontMetrics fm(painter.fontMetrics());

    const int extraAreaWidth = d->extraArea->width();

    painter.fillRect(event->rect(), palette.color(QPalette::Base));
    painter.fillRect(event->rect().intersected(QRect(0, 0, extraAreaWidth, INT_MAX)), palette.color(QPalette::Background));

    QTextBlock block = this->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top;

    while (block.isValid() && top <= event->rect().bottom()) {

        top = bottom;
        bottom = top + (int)blockBoundingRect(block).height();
        QTextBlock nextBlock = block.next();

        QTextBlock nextVisibleBlock = nextBlock;
        int nextVisibleBlockNumber = blockNumber + 1;

        if (!nextVisibleBlock.isVisible()) {
#if QT_VERSION >= 0x040500
            nextVisibleBlock = this->document()->findBlockByLineNumber(nextVisibleBlock.firstLineNumber());
#else
	    nextVisibleBlock = this->document()->findBlockByNumber(nextVisibleBlock.blockNumber());
#endif
            nextVisibleBlockNumber = nextVisibleBlock.blockNumber();
        }

        painter.setPen(palette.color(QPalette::Dark));

        if (d->showRevisions && block.revision() != documentLayout->lastSaveRevision) {
            painter.save();
            painter.setRenderHint(QPainter::Antialiasing, false);
            if (block.revision() < 0)
                painter.setPen(QPen(Qt::darkGreen, 2));
            else
                painter.setPen(QPen(Qt::red, 2));
            painter.drawLine(extraAreaWidth-1, top, extraAreaWidth-1, bottom-1);
            painter.restore();
        }

        if (d->showLineNumbers) {
            const QString &number = QString::number(blockNumber + 1);
            painter.drawText(0, top, extraAreaWidth - 4, fm.height(), Qt::AlignRight, number);
        }

        block = nextVisibleBlock;
        blockNumber = nextVisibleBlockNumber;
    }
}

void dtkTextEditor::onBlockCountChanged(int) // >> slotUpdateExtraAreaWidth in basetexteditor.cpp
{   
    this->onUpdateExtraAreaWidth();
}

void dtkTextEditor::onUpdateExtraAreaWidth(void)
{
    this->setViewportMargins(this->extraAreaWidth(), 0, 0, 0);
}

void dtkTextEditor::onModificationChanged(bool changed)
{
    if (changed)
        return;

    dtkTextEditorDocumentLayout *documentLayout = qobject_cast<dtkTextEditorDocumentLayout*>(this->document()->documentLayout());
    int oldLastSaveRevision = documentLayout->lastSaveRevision;
    documentLayout->lastSaveRevision = this->document()->revision();

    if (oldLastSaveRevision != documentLayout->lastSaveRevision) {
        QTextBlock block = this->document()->begin();
        while (block.isValid()) {
            if (block.revision() < 0 || block.revision() != oldLastSaveRevision) {
                block.setRevision(-documentLayout->lastSaveRevision - 1);
            } else {
                block.setRevision(documentLayout->lastSaveRevision);
            }
            block = block.next();
        }
    }
    d->extraArea->update();
}

void dtkTextEditor::onUpdateRequest(const QRect &r, int dy)
{
    if (dy)
        d->extraArea->scroll(0, dy);
    else if (r.width() > 4) { // wider than cursor width, not just cursor blinking
        d->extraArea->update(0, r.y(), d->extraArea->width(), r.height());
    }

    if (r.contains(viewport()->rect()))
        this->onUpdateExtraAreaWidth();
}

void dtkTextEditor::onCursorPositionChanged(void)
{
    this->viewport()->update();
}

QString dtkTextEditor::textUnderCursor(void) const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

// /////////////////////////////////////////////////////////////////
// CREDITS
// /////////////////////////////////////////////////////////////////

/*******************************************************************
 **
 ** Some parts of this file are part of Qt Creator
 **
 ** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
 **
 ** Contact:  Qt Software Information (qt-info@nokia.com)
 **
 ** Commercial Usage
 **
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 **
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** If you are unsure which license is appropriate for your use, please
 ** contact the sales department at qt-sales@nokia.com.
 **
 ******************************************************************/
