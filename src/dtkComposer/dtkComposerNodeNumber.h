/* dtkComposerNodeNumber.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Feb 25 16:19:59 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 16:46:40 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 134
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODENUMBER_H
#define DTKCOMPOSERNODENUMBER_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeNumberPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumber : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeNumber(dtkComposerNode *parent = 0);
    ~dtkComposerNodeNumber(void);

public:
    virtual const QVariant::Type genre(void) const = 0;

public:
    void  setLabelText(const QString& value);
    void setEditorText(const QString& value);

    void  interactiveOn(void);
    void interactiveOff(void);

public:
    QString editorText(void) const; 

protected:
    bool isInteractive(void) const;

public:
    void expand(void);
    void collapse(void);

protected slots:
    void onCollapseFinised(void);

private:
    dtkComposerNodeNumberPrivate *d;
};

#endif
