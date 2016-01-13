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

#include <QtWidgets>

#include "dtkMonitoringExport.h"

class DTKMONITORING_EXPORT dtkMonitoringScene : public QGraphicsScene
{
public:
     dtkMonitoringScene(QObject *parent = 0);
    ~dtkMonitoringScene(void);

private:
    class dtkMonitoringScenePrivate *d;
};

//
// dtkMonitoringScene.h ends here
