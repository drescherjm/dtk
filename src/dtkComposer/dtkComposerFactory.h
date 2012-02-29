/* dtkComposerFactory.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:17
 * Version: $Id$
 * Last-Updated: Wed Feb 29 01:38:31 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 52
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
    QList<QString> nodes(void);
    QHash<QString, QString> descriptions(void);
    QHash<QString, QStringList> tags(void);
    QHash<QString, QString> types(void);

private:
    dtkComposerFactoryPrivate *d;
};

#endif
