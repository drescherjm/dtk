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

protected:
     virtual void dragEnterEvent(QGraphicsSceneDragDropEvent * event);
     virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent * event);
     virtual void dragMoveEvent (QGraphicsSceneDragDropEvent * event);
     virtual void dropEvent     (QGraphicsSceneDragDropEvent * event);

private:
    class dtkMonitoringScenePrivate *d;
};

//
// dtkMonitoringScene.h ends here
