/* dtkTextEditorSyntaxHighlighter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Apr 15 00:28:50 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 15 13:12:48 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKTEXTEDITORSYNTAXHIGHLIGHTER_H
#define DTKTEXTEDITORSYNTAXHIGHLIGHTER_H

#include "dtkGuiExport.h"

#include <QSyntaxHighlighter>

class dtkTextEditor;
class dtkTextEditorSyntaxHighlighterPrivate;

class DTKGUI_EXPORT dtkTextEditorSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
        
public:
     dtkTextEditorSyntaxHighlighter(dtkTextEditor *editor = 0);
    ~dtkTextEditorSyntaxHighlighter(void);

    struct dtkTextEditorHighlightingRule {
        QRegExp pattern;
        QTextCharFormat format;
    };

protected:
    void setupKeywords            (QStringList patterns, QTextCharFormat format);
    void setupVariable            (QRegExp pattern, QTextCharFormat format);
    void setupClass               (QRegExp pattern, QTextCharFormat format);
    void setupFunction            (QRegExp pattern, QTextCharFormat format);
    void setupQuotation           (QRegExp pattern, QTextCharFormat format);
    void setupSingleLineComment   (QRegExp pattern, QTextCharFormat format);
    void setupMultiLineComment    (QRegExp startPattern, QRegExp endPattern, QTextCharFormat format);
    void setupDecimalNumber       (QRegExp pattern, QTextCharFormat format);
    void setupFloatingPointNumber (QRegExp pattern, QTextCharFormat format);
    void setupOctalNumber         (QRegExp pattern, QTextCharFormat format);
    void setupHexNumber           (QRegExp pattern, QTextCharFormat format);

protected:
    void highlightBlock(const QString &text);

private:
    dtkTextEditorSyntaxHighlighterPrivate *d;
};

#endif
