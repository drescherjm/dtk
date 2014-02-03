/* %NodeName%.cpp ---
 *
 * Author: %Author%
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkComposer/dtkComposerTransmitterEmitter.h>
#include <dtkComposer/dtkComposerTransmitterReceiver.h>

#include <dtkLog/dtkLog.h>

#include "%NodeName%.h"

// /////////////////////////////////////////////////////////////////
// %NodeName%Private interface
// /////////////////////////////////////////////////////////////////

class %NodeName%Private
{
public:
    /*
      Here one must declare the pointer to the process that is wrapped by
      the node.
    */
    %WrappedClass% *process;

public:
    /*
      Here one must declare the inputs of the node using
      dtkComposerTransmitterReceiver<T>, eg:
      \code
      dtkComposerTransmitterReceiver<qlonglong> receiver_index;
      dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;
      dtkComposerTransmitterReceiverVector<dtkAbstractProcess> receiver_process_array;
      \endcode
    */

public:
    /*
      Here one must declare the outputs of the node using
      dtkComposerTransmitterEmitter<T>, eg:
      \code
      dtkComposerTransmitterEmitter<dtkAbstractProcess> emitter_data;
      dtkComposerTransmitterEmitterVector<qreal> emitter_scalar_array;
      \endcode
    */

public:
    /*
      Additional variables are sometimes necessary, one can declare
      them right here.
     */
};

// /////////////////////////////////////////////////////////////////
// %NodeName% implementation
// /////////////////////////////////////////////////////////////////

//! Node constructor
/*
    Here the declared receivers must be appended to the current
    node.

    \code
    this->appendReceiver(&(d->receiver_index));
    this->appendReceiver(&(d->receiver_vector));
    this->appendReceiver(&(d->receiver_process_array));
    \endcode

    Then the declared emitters must be appended to the current
    node.

    \code
    this->appendEmitter(&(d->emitter_data));
    this->appendEmitter(&(d->emitter_scalar_array));
    \endcode
 */
%NodeName%::%NodeName%(void) : dtkComposerNodeLeafProcess(), d(new %NodeName%Private)
{
    d->process = NULL;
}

//! Node destructor
/*
    If the node is the owner of the wrapped process, one must delete the
    related pointer as follows:

    \code
    if (d->process)
        delete d->process;
    d->process = NULL;
    \endcode
 */
%NodeName%::~%NodeName%(void)
{
    this->clearProcess();

    delete d;

    d = NULL;
}

//! Returns the string that enables the node factory to identify the
//! node.
/*
    By convention, this string is the name of the node class minus the
    root part "ComposerNode".
 */
QString %NodeName%::type(void)
{
    return "%NodeName%"; // Do not forget to remove "ComposerNode" from type name.
}

//! Returns the title of the node that appears in the composer GUI.
QString %NodeName%::titleHint(void)
{
    return "%WrappedClass%";
}

//! Returns the name of the input identified by its index \a port.
QString %NodeName%::inputLabelHint(int port)
{
    //  Here is a sample of what you can write. (You can erase it of
    //  course ;-) !)

    /*
    switch (port) {
    case 0:
        return "index";
    case 1:
        return "vector";
    case 2:
        return "process array";
    default:
        return dtkComposerNodeLeaf::inputLabelHint(port);
    }
    */
}

//! Returns the name of the output identified by its index \a port.
QString %NodeName%::outputLabelHint(int port)
{
    /*
    switch (port) {
    case 0:
        return "data";
    case 1:
        return "scalar array";
    default:
        return dtkComposerNodeLeaf::outputLabelHint(port);
    }
    */
}
   
//! Return true if the wrapped process is abstract.
bool %NodeName%::isAbstractProcess(void) const 
{
    // Uncomment the line you need (Please, erase the other line and
    // this comment ;-) ).

    /* return false; */
    /* return true;  */
}

//! Returns identifier of the wrapped process.
QString %NodeName%::abstractProcessType(void) const 
{ 
    return "%WrappedClass%"; 
}

void %NodeName%::setProcess(dtkAbstractProcess *process)
{
    d->process = dynamic_cast<%WrappedClass% *>(process);
}

dtkAbstractProcess *%NodeName%::process(void) const
{
    return d->process;
}

//! Executes the logic of the node.
void %NodeName%::run(void)
{
    //  Here is a sample of what can be the logic of a process node. (You
    //  can erase it of course ;-) !)

    /* 
    if (!d->receiver_index.isEmpty() && !d->receiver_vector.isEmpty() && !d->receiver_process_array.isEmpty()) {

        if (!d->process) {
            dtkWarn() << Q_FUNC_INFO << "No process instanciated, abort:"<< this->currentImplementation();
            d->emitter_data.clearData();
            d->emitter_scalar_array.clearData();
            return;
        }

        qlonglong index = *d->receiver_index.process();
        dtkVectorReal *vector = d->receiver_vector.process();
        dtkContainerVector<dtkAbstractProcess*> *process_array = d->receiver_process_array.process();

        d->process->setParamater(index, 0);
        
        for(int i = 0; i < vector->size(); ++i)
            d->process->setParamater(*vector[i], i+1);
        
        d->process->setData(process_array->first());

        d->process->update();

        d->emitter_process.setData(d->process->output());
        d->emitter_scalar_array.setProcess(reinterpret_cast<dtkContainerVector<qreal> *>(d->process->data()));

    } else {
        dtkWarn() << Q_FUNC_INFO << "The input are not all set. Nothing is done.";
        d->emitter_data.clearData();
        d->emitter_scalar_array.clearData();
        return;
    }
    */
}
