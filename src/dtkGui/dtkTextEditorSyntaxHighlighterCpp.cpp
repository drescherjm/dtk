/* dtkTextEditorSyntaxHighlighterCpp.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Apr 15 11:08:17 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 15 13:39:02 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkTextEditor.h>
#include <dtkTextEditorSyntaxHighlighterCpp.h>

dtkTextEditorSyntaxHighlighterCpp::dtkTextEditorSyntaxHighlighterCpp(dtkTextEditor *editor) : dtkTextEditorSyntaxHighlighter(editor)
{
    { // -- Keywords
    QStringList keywords;
    keywords 
        << "\\band\\b"
        << "\\band_eq\\b"
        << "\\basm\\b"
        << "\\bbitand\\b"
        << "\\bbitor\\b"
        << "\\bbreak\\b"
        << "\\bcase\\b"
        << "\\bcatch\\b"
        << "\\bcompl\\b"
        << "\\bconst_cast\\b"
        << "\\bcontinue\\b"
        << "\\bdefault\\b"
        << "\\bdelete\\b"
        << "\\bdo\\b"
        << "\\bdynamic_cast\\b"
        << "\\belse\\b"
        << "\\bfor\\b"
        << "\\bfortran\\b"
        << "\\bfriend\\b"
        << "\\bgoto\\b"
        << "\\bif\\b"
        << "\\bnew\\b"
        << "\\bnot\\b"
        << "\\bnot_eq\\b"
        << "\\boperator\\b"
        << "\\bor\\b"
        << "\\bor_eq\\b"
        << "\\bprivate\\b"
        << "\\bprotected\\b"
        << "\\bpublic\\b"
        << "\\breinterpret_cast\\b"
        << "\\breturn\\b"
        << "\\bsizeof\\b"
        << "\\bstatic_cast\\b"
        << "\\bswitch\\b"
        << "\\bthis\\b"
        << "\\bthrow\\b"
        << "\\btry\\b"
        << "\\btypeid\\b"
        << "\\busing\\b"
        << "\\bwhile\\b"
        << "\\bxor\\b"
        << "\\bxor_eq\\b";

    QTextCharFormat format;
    format.setForeground(Qt::darkMagenta);
    format.setFontWeight(QFont::Bold);
    this->setupKeywords(keywords, format);
    }
 
    { // -- Types
    QStringList keywords;
    keywords        
        << "\\bauto\\b"
        << "\\bbool\\b"
        << "\\bchar\\b"
        << "\\bclass\\b"
        << "\\bconst\\b"
        << "\\bdouble\\b"
        << "\\benum\\b"
        << "\\bexplicit\\b"
        << "\\bexport\\b"
        << "\\bextern\\b"
        << "\\bfloat\\b"
        << "\\binline\\b"
        << "\\bint\\b"
        << "\\blong\\b"
        << "\\bmutable\\b"
        << "\\bnamespace\\b"
        << "\\bregister\\b"
        << "\\bshort\\b"
        << "\\bsigned\\b"
        << "\\bstatic\\b"
        << "\\bstruct\\b"
        << "\\btemplate\\b"
        << "\\btypedef\\b"
        << "\\btypename\\b"
        << "\\bunion\\b"
        << "\\bunsigned\\b"
        << "\\bvirtual\\b"
        << "\\bvoid\\b"
        << "\\bvolatile\\b"
        << "\\bwchar_t\\b";

    QTextCharFormat format;
    format.setForeground(Qt::darkBlue);
    format.setFontWeight(QFont::Bold);
    this->setupKeywords(keywords, format);
    }

    { // -- Macros
    QStringList keywords;
    keywords 
        << "\\bNULL\\b"
        << "\\bTRUE\\b"
        << "\\bFALSE\\b"
        << "\\bMAX\\b"
        << "\\bMIN\\b"
        << "\\b__LINE__\\b"
        << "\\b__DATA__\\b"
        << "\\b__FILE__\\b"
        << "\\b__TIME__\\b"
        << "\\b__STDC__\\b"
        << "\\bfalse\\b"
        << "\\btrue\\b";

    QTextCharFormat format;
    format.setForeground(QColor(255, 123, 80));
    format.setFontWeight(QFont::Bold);
    this->setupKeywords(keywords, format);
    }

    { // -- Preprocessor definitions
    QStringList keywords;
    keywords 
        << "\\bifdef\\b"
        << "\\bifndef\\b"
        << "\\belif\\b"
        << "\\bdefine\\b"
        << "\\bendif\\b"
        << "\\bundef\\b";

    QTextCharFormat format;
    format.setForeground(QColor(25, 123, 180));
    format.setFontWeight(QFont::Bold);
    this->setupKeywords(keywords, format);
    }

    { // -- Includes and pragmas
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(Qt::darkGreen);
    setupClass(QRegExp("^#[ \t]*(include|pragma)"), format);
    }

    { // -- Classes
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(Qt::darkMagenta);
    setupClass(QRegExp("\\bdtk[A-Za-z]+\\b"), format);
    }

    { // -- Functions
    QTextCharFormat format;
    format.setFontItalic(true);
    format.setForeground(Qt::blue);
    setupFunction(QRegExp("\\b[A-Za-z0-9_]+(?=\\()"), format);
    }

    { // -- Quotation
    QTextCharFormat format;
    format.setForeground(Qt::darkGreen);
    setupQuotation(QRegExp("\".*\""), format);
    }

    { // -- Singleline comment
    QTextCharFormat format;
    format.setForeground(Qt::red);
    setupSingleLineComment(QRegExp("//[^\n]*"), format);
    }

    { // -- Multiline comment
    QTextCharFormat format;
    format.setForeground(Qt::red);
    this->setupMultiLineComment(QRegExp("/\\*"), QRegExp("\\*/"), format);
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
