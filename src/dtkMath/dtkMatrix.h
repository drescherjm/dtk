/* dtkMatrix.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 15:58:33 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Jul 16 10:31:23 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 82
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
    enum Type {
	Integer,
	Double
    };
    
public:
             dtkMatrix(QObject *parent = 0);
    virtual ~dtkMatrix(void);

    void setType(Type type);

public:
    template <typename T> T at(int i);

private:
    dtkMatrixPrivate *d;
};

DTK_DECLARE_OBJECT(dtkMatrix *)
DTK_DECLARE_PLUGIN(dtkMatrix)
DTK_DECLARE_PLUGIN_FACTORY(dtkMatrix)
DTK_DECLARE_PLUGIN_MANAGER(dtkMatrix)

#include "dtkMatrix.tpp"
