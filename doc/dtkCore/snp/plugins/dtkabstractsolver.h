/* interfaces.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: ven. avril 11 09:37:16 2014 (+0200)
 */

/* Change Log:
 * 
 */

//![0]
#pragma once

#include <QObject>

class dtkAbstractSolver : public QObject
{
    Q_OBJECT

public:
    virtual ~dtkAbstractSolver(void) {;}

public:
    virtual void setMethod(const QString& method) = 0;
    virtual int solve(void) = 0;
    virtual QString result(void) = 0;
};

Q_DECLARE_INTERFACE(dtkAbstractSolver, "fr.inria.dtkAbstractSolver")
//! [0]
