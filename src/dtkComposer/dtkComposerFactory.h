/* dtkComposerFactory.h ---
 *
 * Author: Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:17
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtCore>

class dtkComposerFactoryPrivate;
class dtkComposerNode;

class  dtkComposerFactory : public QObject
{
    Q_OBJECT

public:
             dtkComposerFactory(void);
    virtual ~dtkComposerFactory(void);

public:
    void initComposerMetatypes(void);

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

