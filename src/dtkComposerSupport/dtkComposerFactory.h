/* dtkComposerFactory.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:17
 * Version: $Id$
 * Last-Updated: Tue Oct 23 11:38:24 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 65
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERFACTORY_H
#define DTKCOMPOSERFACTORY_H

#include "dtkComposerSupportExport.h"

#include <QtCore>

class dtkComposerFactoryPrivate;
class dtkComposerNode;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerFactory : public QObject
{
    Q_OBJECT

public:
    dtkComposerFactory(void);
    virtual ~dtkComposerFactory(void);

public:
    void initNodeNumberOperatorUnary(void);
    void initNodeNumberOperatorBinary(void);
    void initNodeBooleanOperators(void);

    void initNodeVectorInteger(void);
    void initNodeVectorReal(void);
    void initNodeMatrixSquareReal(void);

    void initNodeVector3D(void);
    void initNodeQuaternion(void);

    void initNodeArrayScalar(void);

    void initNodeContainerData(void);

    void initNodeControl(void);

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
