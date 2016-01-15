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
     void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
     void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
     void dragMoveEvent (QGraphicsSceneDragDropEvent *event);
     void dropEvent     (QGraphicsSceneDragDropEvent *event);

     void keyPressEvent(QKeyEvent *event);

private:
    class dtkMonitoringScenePrivate *d;
};

//
// dtkMonitoringScene.h ends here
