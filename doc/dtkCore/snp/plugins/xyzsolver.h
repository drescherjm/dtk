/* implementations.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: ven. avril 11 10:27:52 2014 (+0200)
 */

/* Change Log:
 * 
 */

//![0]
#pragma once

#include "dtkabstractsolver.h"

#include <QtPlugin>
#include <QStringList>
#include <QImage>

class xyzSolverPlugin : public dtkAbstractSolver
{
    Q_OBJECT
    Q_INTERFACES(dtkAbstractSolver)
    Q_PLUGIN_METADATA(IID "fr.inria.xyzSolverPlugin" FILE "xyzSolverPlugin.json")

public:
     xyzSolverPlugin(void) {}
    ~xyzSolverPlugin(void) {}

public:
    void setMethod(const QString& method);
    int solve(void);
    QString result(void);
};
//! [0]
