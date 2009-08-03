/* dtkTextEditorSyntaxHighlighterTcl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Apr 15 13:04:11 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 15 13:38:53 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkTextEditor.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterTcl.h>

dtkTextEditorSyntaxHighlighterTcl::dtkTextEditorSyntaxHighlighterTcl(dtkTextEditor *editor) : dtkTextEditorSyntaxHighlighter(editor)
{
    { // -- Keywords
    QStringList keywords;
    keywords 
        << "\\btcl\\b"
        << "\\bstring\\b"
        << "\\bsubst\\b"
        << "\\bregexp\\b"
        << "\\bregsub\\b"
        << "\\bscan\\b"
        << "\\bformat\\b"
        << "\\bbinary\\b"

        << "\\blist\\b"
        << "\\bsplit\\b"
        << "\\bjoin\\b"
        << "\\bconcat\\b"
        << "\\bllength\\b"
        << "\\blrange\\b"
        << "\\blsearch\\b"
        << "\\blreplace\\b"
        << "\\blindex\\b"
        << "\\blsort\\b"
        << "\\blinsert\\b"
        << "\\blrepeat\\b"
        << "\\bdict\\b"

        << "\\bif\\b"
        << "\\belse\\b"
        << "\\belseif\\b"
        << "\\bthen\\b"
        << "\\bfor\\b"
        << "\\bforeach\\b"
        << "\\bswitch\\b"
        << "\\bcase\\b"
        << "\\bwhile\\b"
        << "\\bcontinue\\b"
        << "\\breturn\\b"
        << "\\bbreak\\b"
        << "\\bcatch\\b"
        << "\\berror\\b"
        << "\\beval\\b"
        << "\\buplevel\\b"
        << "\\bafter\\b"
        << "\\bupdate\\b"
        << "\\bvwait\\b"

        << "\\bproc\\b"
        << "\\brename\\b"
        << "\\bset\\b"
        << "\\blset\\b"
        << "\\blassign\\b"
        << "\\bunset\\b"
        << "\\bnamespace\\b"
        << "\\bvariable\\b"
        << "\\bupvar\\b"
        << "\\bglobal\\b"
        << "\\btrace\\b"
        << "\\barray\\b"
        << "\\bincr\\b"
        << "\\bappend\\b"
        << "\\blappend\\b"
        << "\\bexpr\\b"

        << "\\bfile\\b"
        << "\\bopen\\b"
        << "\\bclose\\b"
        << "\\bsocket\\b"
        << "\\bfconfigure\\b"
        << "\\bputs\\b"
        << "\\bgets\\b"
        << "\\bread\\b"
        << "\\bseek\\b"
        << "\\btell\\b"
        << "\\beof\\b"
        << "\\bflush\\b"
        << "\\bfblocked\\b"
        << "\\bfcopy\\b"
        << "\\bfileevent\\b"

        << "\\bsource\\b"
        << "\\bload\\b"
        << "\\bunload\\b"
        << "\\bpackage\\b"

        << "\\binfo\\b"
        << "\\binterp\\b"
        << "\\bhistory\\b"
        << "\\bbgerror\\b"
        << "\\bunknown\\b"
        << "\\bmemory\\b"
        << "\\bcd\\b"
        << "\\bpwd\\b"
        << "\\bclock\\b"
        << "\\btime\\b"
        << "\\bexec\\b"
        << "\\bglob\\b"
        << "\\bpid\\b"
        << "\\bexit\\b";        

    QTextCharFormat format;
    format.setForeground(Qt::darkBlue);
    format.setFontWeight(QFont::Bold);
    this->setupKeywords(keywords, format);
    }

    { // -- Variables
    QTextCharFormat format;
    format.setForeground(Qt::darkRed);
    setupVariable(QRegExp("[$@%][$]?[a-zA-Z_][a-zA-Z0-9_]*"), format);
    }

    { // -- Quotation
    QTextCharFormat format;
    format.setForeground(Qt::darkGreen);
    setupQuotation(QRegExp("\".*\""), format);
    setupQuotation(QRegExp("'.*'"), format);
    }

    { // -- Singleline comment
    QTextCharFormat format;
    format.setForeground(Qt::red);
    setupSingleLineComment(QRegExp("#[^\n]*"), format);
    }

    { // -- Multiline comment
    QTextCharFormat format;
    format.setForeground(Qt::red);
    this->setupMultiLineComment(QRegExp("'''"),    QRegExp("'''"),    format);
    this->setupMultiLineComment(QRegExp("\"\"\""), QRegExp("\"\"\""), format);
    }

    { // -- Decimal number
    QTextCharFormat format;
    format.setForeground(Qt::darkYellow);
    this->setupDecimalNumber(QRegExp("\\b([1-9][0-9]*|0)([Uu]([Ll]|LL|ll)?|([Ll]|LL|ll)[Uu]?)?\\b"), format);
    }

    { // -- Floating point number
    QTextCharFormat format;
    format.setForeground(Qt::darkBlue);
    this->setupFloatingPointNumber(QRegExp("\\b([0-9]+[Ee][-]?[0-9]+|([0-9]*.[0-9]+|[0-9]+.)([Ee][-]?[0-9]+)?)[fFlL]?\\b"), format);
    }

    { // -- Octal number
    QTextCharFormat format;
    format.setForeground(Qt::cyan);
    this->setupOctalNumber(QRegExp("\\b0[0-7]+([Uu]([Ll]|LL|ll)?|([Ll]|LL|ll)[Uu]?)?\\b"), format);
    }

    { // -- Hex number
    QTextCharFormat format;
    format.setForeground(Qt::green);
    this->setupHexNumber(QRegExp("\\b0[xX][0-9a-fA-F]+([Uu]([Ll]|LL|ll)?|([Ll]|LL|ll)[Uu]?)?\\b"), format);
    }
}
