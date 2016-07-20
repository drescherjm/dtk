// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

//![0]
#pragma once

#include "dtkabstractsolver.h"

#include <QtCore>

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

//
// xyzsolver.h ends here
