/* dtkMatrix.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 15:58:33 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Jul 16 14:50:59 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 206
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkMatrix_p.h"

class dtkMatrix : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qulonglong colCount READ colCount)
    Q_PROPERTY(qulonglong rowCount READ rowCount)

public:
    virtual qulonglong colCount(void) const = 0;
    virtual qulonglong rowCount(void) const = 0;

public:
    virtual QVariant at(qulonglong i, qulonglong j) const = 0;

public:
    virtual void allocate(qulonglong r, qulonglong c) = 0;
};

QDebug operator<<(QDebug debug, const dtkMatrix *matrix);
QDebug operator<<(QDebug debug, const dtkMatrix& matrix);

DTK_DECLARE_OBJECT(dtkMatrix *)
DTK_DECLARE_PLUGIN(dtkMatrix)
DTK_DECLARE_PLUGIN_FACTORY(dtkMatrix)
DTK_DECLARE_PLUGIN_MANAGER(dtkMatrix)
