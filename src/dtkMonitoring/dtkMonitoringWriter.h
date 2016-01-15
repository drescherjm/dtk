/* dtkMonitoringWriter.h ---
 *
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkMonitoringExport.h"

#include <QtCore>

#include <QDomDocument>

class dtkMonitor;
class dtkMonitoringScene;
class dtkMonitoringWriterPrivate;

class  DTKMONITORING_EXPORT dtkMonitoringWriter
{
public:
             dtkMonitoringWriter(void);
    virtual ~dtkMonitoringWriter(void);

public:
    void setScene(dtkMonitoringScene *scene);

public:
   QDomDocument toXML();

public:
   void write(const QString& filename);

protected:
   void toXML(dtkMonitor* monitor, QDomElement& elmt);

private:
    dtkMonitoringWriterPrivate *d;
};

