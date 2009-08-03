/* dtkTextEditorSyntaxHighlighter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Apr 15 00:32:02 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 15 13:13:11 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 49
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 15-Apr-2009    Julien Wintz  
 *    Last-Updated: Wed Apr 15 13:01:27 2009 (+0200) #47 (Julien Wintz)
 *    Initial revision. Method basically behave the same, later
 *    revisions will distinguish them.
 * 
 */

#include <dtkGui/dtkTextEditor.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighter.h>

class dtkTextEditorSyntaxHighlighterPrivate
{
public:
    QRegExp         multiLineCommentStartExpression;
    QRegExp         multiLineCommentEndExpression;
    QTextCharFormat multiLineCommentFormat;

    QVector<dtkTextEditorSyntaxHighlighter::dtkTextEditorHighlightingRule> rules;
};

dtkTextEditorSyntaxHighlighter::dtkTextEditorSyntaxHighlighter(dtkTextEditor *editor) : QSyntaxHighlighter(editor->document())
{
    d = new dtkTextEditorSyntaxHighlighterPrivate;
}

dtkTextEditorSyntaxHighlighter::~dtkTextEditorSyntaxHighlighter(void)
{
    delete d;
}

void dtkTextEditorSyntaxHighlighter::setupKeywords(QStringList patterns, QTextCharFormat format)
{
    dtkTextEditorHighlightingRule rule;
    foreach (const QString &pattern, patterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = format;
        d->rules << rule;
    }
}

void dtkTextEditorSyntaxHighlighter::setupVariable(QRegExp pattern, QTextCharFormat format)
{
    dtkTextEditorHighlightingRule rule;
    rule.pattern = QRegExp(pattern);
    rule.format  = format;
    d->rules << rule;
}

void dtkTextEditorSyntaxHighlighter::setupClass(QRegExp pattern, QTextCharFormat format)
{
    dtkTextEditorHighlightingRule rule;
    rule.pattern = QRegExp(pattern);
    rule.format  = format;
    d->rules << rule;
}

void dtkTextEditorSyntaxHighlighter::setupFunction(QRegExp pattern, QTextCharFormat format)
{
    dtkTextEditorHighlightingRule rule;
    rule.pattern = QRegExp(pattern);
    rule.format  = format;
    d->rules << rule;
}

void dtkTextEditorSyntaxHighlighter::setupQuotation(QRegExp pattern, QTextCharFormat format)
{
    dtkTextEditorHighlightingRule rule;
    rule.pattern = QRegExp(pattern);
    rule.format  = format;
    d->rules << rule;
}

void dtkTextEditorSyntaxHighlighter::setupSingleLineComment(QRegExp pattern, QTextCharFormat format)
{
    dtkTextEditorHighlightingRule rule;
    rule.pattern = QRegExp(pattern);
    rule.format  = format;
    d->rules << rule;
}

void dtkTextEditorSyntaxHighlighter::setupMultiLineComment(QRegExp startPattern, QRegExp endPattern, QTextCharFormat format)
{
    d->multiLineCommentStartExpression = QRegExp(startPattern);
    d->multiLineCommentEndExpression = QRegExp(endPattern);
    d->multiLineCommentFormat = format;
}

void dtkTextEditorSyntaxHighlighter::setupDecimalNumber(QRegExp pattern, QTextCharFormat format)
{
    dtkTextEditorHighlightingRule rule;
    rule.pattern = QRegExp(pattern);
    rule.format  = format;
    d->rules << rule;
}

void dtkTextEditorSyntaxHighlighter::setupFloatingPointNumber(QRegExp pattern, QTextCharFormat format)
{
    dtkTextEditorHighlightingRule rule;
    rule.pattern = QRegExp(pattern);
    rule.format  = format;
    d->rules << rule;
}

void dtkTextEditorSyntaxHighlighter::setupOctalNumber(QRegExp pattern, QTextCharFormat format)
{
    dtkTextEditorHighlightingRule rule;
    rule.pattern = QRegExp(pattern);
    rule.format  = format;
    d->rules << rule;
}

void dtkTextEditorSyntaxHighlighter::setupHexNumber(QRegExp pattern, QTextCharFormat format)
{
    dtkTextEditorHighlightingRule rule;
    rule.pattern = QRegExp(pattern);
    rule.format  = format;
    d->rules << rule;
}

// /////////////////////////////////////////////////////////////////
// Here goes highlighting
// /////////////////////////////////////////////////////////////////

void dtkTextEditorSyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (const dtkTextEditorHighlightingRule& rule, d->rules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = d->multiLineCommentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = d->multiLineCommentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + d->multiLineCommentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, d->multiLineCommentFormat);
        startIndex = d->multiLineCommentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
