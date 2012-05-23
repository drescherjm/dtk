/* dtkComposerFactory.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:17
 * Version: $Id$
 * Last-Updated: Tue May 15 16:48:41 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 53
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERFACTORY_H
#define DTKCOMPOSERFACTORY_H

#include "dtkComposerExport.h"

#include <QtCore>

class dtkComposerFactoryPrivate;
class dtkComposerNode;

class DTKCOMPOSER_EXPORT dtkComposerFactory : public QObject
{
    Q_OBJECT

public:
             dtkComposerFactory(void);
    virtual ~dtkComposerFactory(void);

public slots:
    virtual dtkComposerNode *create(const QString& type);

public:
    virtual QList<QString> nodes(void);
    virtual QHash<QString, QString> descriptions(void);
    virtual QHash<QString, QStringList> tags(void);
    virtual QHash<QString, QString> types(void);

private:
    dtkComposerFactoryPrivate *d;
};

#endif
