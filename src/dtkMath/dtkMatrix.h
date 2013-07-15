/* dtkMatrix.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 15:58:33 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Jul 15 16:13:53 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkCore>

class dtkMatrixPrivate;

class dtkMatrix : public QObject
{
    Q_OBJECT

public:
             dtkMatrix(QObject *parent = 0);
    virtual ~dtkMatrix(void);

private:
    dtkMatrixPrivate *d;
};

DTK_DECLARE_OBJECT(dtkMatrix*)
DTK_DECLARE_PLUGIN(dtkMatrix)
DTK_DECLARE_PLUGIN_FACTORY(dtkMatrix)
DTK_DECLARE_PLUGIN_MANAGER(dtkMatrix)
