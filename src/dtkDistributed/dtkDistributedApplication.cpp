/* dtkDistributedApplication.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/04 12:31:06
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkDistributed.h"
#include "dtkDistributedApplication.h"
#include "dtkDistributedApplicationPrivate.h"
#include "dtkDistributedCommunicator"
#include "dtkDistributedSettings.h"
#include "dtkDistributedPolicy.h"

#include <dtkLog>

/*!
  \class dtkDistributedApplication
  \inmodule dtkDistributed

  \brief This class is used to start non GUI applications that use the dtkDistributed framework. The distributed option (plugins, number of process/threads, ...) can be configured on the command line, and also setup settings and dtkLog.

    \code
int main(int argc, char **argv)
{
  dtkDistributedApplication *app = dtkDistributed::create(argc, argv);
  app->setOrganizationName("inria");
  app->setOrganizationDomain("fr");
  app->setApplicationName("myApp");
  app->setApplicationVersion("0.1.0");

  QCommandLineParser *parser = app->parser();
  parser->setApplicationDescription("my dtk distributed app.");

  QCommandLineOption myOption("myopt", "enable myopt", "default val");
  parser->addOption(myOption);

  app->initialize();

  // ------------ check parameters
   if (!parser->isSet(myOption)) {
    qFatal("Error: input are not correctly set! you have to set : --myopt <val>") ;
    return 1;
  }

  // /////////////////////////////////////////////////////////////////
  // Launch the execution
  // ////////////////////////////////////////////////////////////////
  myRunnableClass torun;

  torun.myarg = parser->value(myOption);

  app->spawn();
  app->exec(&torun);
  app->unspawn();
  return 0;
}
    \endcode

    \sa dtkDistributedGuiApplication

*/

/*! \fn dtkDistributedApplication::dtkDistributedApplication(int &argc, char **argv)

Constructs a dtkDistributedApplication.

The \a argc and \a argv arguments are processed by the application, and made available in a more convenient form by the arguments() function.

Warning: The data referred to by \a argc and \a argv must stay valid for the entire lifetime of the dtkCoreApplication object. In addition, argc must be greater than zero and argv must contain at least one valid character string.
*/

dtkDistributedApplication::dtkDistributedApplication(int &argc, char **argv): QCoreApplication(argc, argv)
{

    d = new dtkDistributedApplicationPrivate;
}

/*! \fn dtkDistributedApplication::~dtkDistributedApplication(void)

Destroys the dtkDistributedApplication object.

*/

dtkDistributedApplication::~dtkDistributedApplication(void)
{
    delete d;
    d = NULL;
}

/*! \fn void dtkDistributedApplication::initialize(void)

 Initialize the command line parser. Should be called once all the specific options of your application are added in the parser.

 \sa parser
*/

void dtkDistributedApplication::initialize(void)
{
    d->initialize();
}

/*! \fn void dtkDistributedApplication::exec(QRunnable *task)

  execute the given QRunnable \a task on the spawned processes/threads. Must be called after spawn()

  \sa spawn
*/
void dtkDistributedApplication::exec(QRunnable *task)
{
    d->policy.communicator()->exec(task);
}

/*! \fn void dtkDistributedApplication::spawn (QMap <QString,QString> options)

  Spawn processes/threads on one or several hosts (depending on the implementation). This step can be bypassed if the --no-spawn argument is given. This can be useful when you are using an mpi communicator and your mpi implementation or scheduler does not handle the \a Mpi_comm_Spawn gracefully. Will you have to use an external tool to spawn the application (mpirun , srun , ...)

*/

void dtkDistributedApplication::spawn(QMap<QString,QString> options)
{
    d->spawn();
}

/*! \fn void dtkDistributedApplication::unspawn(void)

  unspawn processes/threads

*/

void dtkDistributedApplication::unspawn(void)
{
    d->unspawn();
}

/*! \fn QCommandLineParser *dtkDistributedApplication::parser(void)

  Return the main QCommandLineParser used by the application. It can be used to app specific options for your application.

*/

QCommandLineParser *dtkDistributedApplication::parser(void)
{
    return d->parser;
}

/*! \fn dtkDistributedPolicy *dtkDistributedApplication::policy(void)

  Return the current policy
*/

dtkDistributedPolicy *dtkDistributedApplication::policy(void)
{
     return &(d->policy);
}

/*! \fn dtkDistributedCommunicator *dtkDistributedApplication::communicator(void)

  Return the main communicator.

  \sa dtkDistributedCommunicator

*/

dtkDistributedCommunicator *dtkDistributedApplication::communicator(void)
{

    return d->policy.communicator();
}

/*! \fn bool dtkDistributedApplication::isMaster(void)

  Return true if the calling process/thread is the master (rank 0)
*/

bool dtkDistributedApplication::isMaster(void)
{
    return (d->policy.communicator()->rank() == 0);
}

/*! \fn void dtkDistributedApplication::noGui(void)

  Always returns true: just to be compatible with dtkDistributedGuiApplication

  \sa spawn
*/

/*  */
bool dtkDistributedApplication::noGui(void)
{
    return true;
}
