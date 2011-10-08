/* dtkComposerExtractor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Oct  6 15:13:27 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct  6 22:08:30 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREXTRACTOR_H
#define DTKCOMPOSEREXTRACTOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

#include <QtCore/QObject>

class dtkComposerScene;
class dtkComposerExtractorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerExtractor : public QObject
{
    Q_OBJECT

public:
    dtkComposerExtractor(dtkComposerScene *scene);
   ~dtkComposerExtractor(void);

   void extract(dtkComposerNode::Attribute attribute);

private:
    dtkComposerExtractorPrivate *d;
};

#endif
