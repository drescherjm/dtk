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

#pragma once

#include <QtCore>

class dtkPluginStoreController : public QObject
{
    Q_OBJECT

public:
     dtkPluginStoreController(void);
    ~dtkPluginStoreController(void);

public:
    Q_INVOKABLE QString arch(void);
    Q_INVOKABLE QString os(void);
};

//
// dtkPluginStoreController.h ends here
