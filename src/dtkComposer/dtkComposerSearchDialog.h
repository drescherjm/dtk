/* dtkComposerSearchDialog.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Nov  5 16:35:28 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once


#include "dtkComposerExport.h"

#include <QtWidgets>

class dtkComposerScene;
class dtkComposerSearchDialogPrivate;
class dtkComposerView;

class DTKCOMPOSER_EXPORT dtkComposerSearchDialog : public QDialog
{
    Q_OBJECT

public:
     dtkComposerSearchDialog(dtkComposerView *parent = 0);
    ~dtkComposerSearchDialog(void);

public:
    void setScene(dtkComposerScene *scene);

protected slots:
    void find(void);
    void next(void);
    void more(void);
    void clear(void);

private:
    dtkComposerSearchDialogPrivate *d;
};

