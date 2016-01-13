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

#include "dtkMonitoringScene.h"

class dtkMonitoringScenePrivate
{
public:
};

dtkMonitoringScene::dtkMonitoringScene(QObject *parent) : QGraphicsScene(parent)
{
    d = new dtkMonitoringScenePrivate;
}

dtkMonitoringScene::~dtkMonitoringScene(void)
{
    delete d;
}

//
// dtkMonitoringScene.cpp ends here
