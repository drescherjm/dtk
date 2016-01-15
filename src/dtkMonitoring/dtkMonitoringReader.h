/* dtkMonitoringReader.h ---
 *
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkMonitor.h"

#include "dtkMonitoringExport.h"

#include <QtCore>

#include <QDomDocument>

class dtkMonitoringScene;
class dtkMonitoringReaderPrivate;

class  DTKMONITORING_EXPORT dtkMonitoringReader
{
public:
             dtkMonitoringReader(void);
    virtual ~dtkMonitoringReader(void);

public:
    void setScene(dtkMonitoringScene *scene);

public:
    void read(const QString& filename);

public:
    void loadSceneFromElement(const QDomElement &document);
    void loadItemFromElement(const QDomElement &document);


private:
    dtkMonitoringReaderPrivate *d;
};

