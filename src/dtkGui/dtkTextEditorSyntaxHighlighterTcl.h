/* dtkTextEditorSyntaxHighlighterTcl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Apr 15 13:03:12 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 15 13:04:02 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKTEXTEDITORSYNTAXHIGHLIGHTERTCL_H
#define DTKTEXTEDITORSYNTAXHIGHLIGHTERTCL_H

#include <dtkGui/dtkTextEditorSyntaxHighlighter.h>

class dtkTextEditorSyntaxHighlighterTcl : public dtkTextEditorSyntaxHighlighter
{
public:
     dtkTextEditorSyntaxHighlighterTcl(dtkTextEditor *editor = 0);
};

#endif
