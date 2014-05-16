/* @(#)dtkDistributedResourceManager.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/25 16:39:26
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedResourceManager.h"


/*! \class dtkDistributedResourceManager
    \inmodule dtkDistributed

    \brief A dtkDistributedResourceManager can reserve computing resources from several resource manager: OAR, Torque and Local

    It abstract the differents manager with a common JSON format exchange.

    When a status request is sent to the dtkDistributedResourceManager, the
output format is :

\code
             {  "version": "<xx.yy>",
                "jobs" : [ { "id" : "<job_id>",
                            "queue" : "<queuename>",
                            "queue_time" : <epoch>,
                            "resources" : { "cores" : <XX>, "nodes" : <yy> },
                            "start_time" : "",
                            "state" : "running|queued|suspended|blocked|exiting|scheduled|unknown",
                            "username" : "<username>",
                            "walltime" : "hh:mm:ss" }
                          , ... ],
                "nodes" : [ { "cores" : [ { "id" : <id0> [, "job" : "<jobid>"]}, ...]
                             "cores_busy" : <ncores_busy>,
                             "cpus" : <ncpus>,
                             "gpus" : <ngpus>,
                             "gpus_busy" : <ngpus_busy>,
                             "name" : "<nodename>",
                             "properties" : { "cpu_arch" : "<x86_64|x86>",
                                              "cpu_model" : "<xeon|opteron>",
                                              "ethernet" : "<1G|10G>",
                                              "properties": {{"key": "value"}, ...},
                                              },
                              "state" : "free|busy|down|standby|absent" }
                          , ... ],
              }
\endcode

example:
\code
             {  "version": "1.0",
                "jobs" : [ { "id" : "6447081",
                            "queue" : "seqextralong",
                            "queue_time" : "1316525900",
                            "resources" : { "cores" : 1, "nodes" : 1 },
                            "start_time" : "",
                            "state" : "running",
                            "username" : "nniclaus",
                            "walltime" : "144:00:00" }, ...],
                "nodes" : [ { "cores" : [ { "id" : 80, "job" : "6447081"},
                                          { "id" : 81 }, { "id" : 82 }, { "id" : 83 },
                                          { "id" : 84 }, { "id" : 85 }, { "id" : 86 },
                                          { "id" : 87 }, { "id" : 88 }]
                             "cores_busy" : 0,
                             "cpus" : 2,
                             "gpus" : 2,
                             "gpus_busy" : 0,
                             "name" : "nefgpu01.inria.fr",
                             "properties" : { "cpu_arch" : "x86_64",
                                              "cpu_model" : "opteron",
                                              "ethernet" : "1G",
                                              "gpu_arch" : "nvidia-1.3",
                                              "gpu_model" : "T10",
                                              "infiniband" : "QDR" },
                              "state" : "free" }, ...]
              }
\endcode


For job submission, the format is:

\code
             {  "resources": {"nodes": 0..N, "cores": 1..M },
                "properties": {{"key": "value"}, ...},
                "walltime": "hh:mm:ss",
                "script": "script_path" | "application": "app_args",
                "queue": "queuename";
                "options": "string"
              }
\endcode


*/

/* \fn dtkDistributedResourceManager::dtkDistributedResourceManager(void)
   Creates the resource manager.
*/

dtkDistributedResourceManager::dtkDistributedResourceManager(void)
{
}

/* \fn dtkDistributedResourceManager::~dtkDistributedResourceManager(void)
   Destroys the resource manager.
*/

dtkDistributedResourceManager::~dtkDistributedResourceManager(void)
{

}


/*! \fn QString dtkDistributedResourceManager::submit (QString input)

  Submit a job, using the job description given in the \a input QString in JSON

*/

/*! \fn QString dtkDistributedResourceManager::deljob (QString jobid)

  Delete a job identified by the \a jobid QString. Returns "OK" or "ERROR" QStrings

*/

/*! \fn QByteArray dtkDistributedResourceManager::status (void)

  Returns the status of the resources (number of jobs, number of processors, etc.)

*/

/*! \fn QString dtkDistributedResourceManager::protocol (void)

  Returns the version of the protocol.

*/
