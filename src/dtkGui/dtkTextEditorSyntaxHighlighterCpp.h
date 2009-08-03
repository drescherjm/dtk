/* dtkTextEditorSyntaxHighlighterCpp.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Apr 15 10:36:03 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 15 12:38:26 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKTEXTEDITORSYNTAXHIGHLIGHTERCPP_H
#define DTKTEXTEDITORSYNTAXHIGHLIGHTERCPP_H

#include "dtkGuiExport.h"

#include <dtkGui/dtkTextEditorSyntaxHighlighter.h>

class DTKGUI_EXPORT dtkTextEditorSyntaxHighlighterCpp : public dtkTextEditorSyntaxHighlighter
{
public:
     dtkTextEditorSyntaxHighlighterCpp(dtkTextEditor *editor = 0);
};

#endif
