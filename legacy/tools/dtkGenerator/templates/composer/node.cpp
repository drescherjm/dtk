/* %1.cpp ---
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

#include <dtkLog>

#include "%1.h"

// /////////////////////////////////////////////////////////////////
// %1Private interface
// /////////////////////////////////////////////////////////////////

class %1Private
{
public:
    /*
      Here one must declare the inputs of the node using
      dtkComposerTransmitterReceiver<T>, eg:

      \code
      dtkComposerTransmitterReceiver<qlonglong> receiver_index;
      dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;
      dtkComposerTransmitterReceiverVector<dtkAbstract%2> receiver_process_array;
      \endcode
    */

public:
    /*
      Here one must declare the outputs of the node using
      dtkComposerTransmitterEmitter<T>, eg:

      \code
      dtkComposerTransmitterEmitter<dtkAbstract%2> emitter_process;
      dtkComposerTransmitterEmitterVector<qreal> emitter_scalar_array;
      \endcode
    */

public:
    /*
      Here one must declare the pointer to the process that is wrapped by
      the node. Uncomment the following line if necessary.

      \code
      %WrappedClass% *process;
      \endcode
     */

public:
    /*
      Additional variables are sometimes necessary, one can declare
      them right here.
     */
};

// /////////////////////////////////////////////////////////////////
// %1 implementation
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
    this->appendEmitter(&(d->emitter_process));
    this->appendEmitter(&(d->emitter_scalar_array));
    \endcode

    Do not forget to set the any pointers to NULL.

    \code
    d->process = NULL;
    \endcode
 */
%1::%1(void) : dtkComposerNodeLeaf%2(), d(new %1Private)
{

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
%1::~%1(void)
{
    delete d;

    d = NULL;
}

//! Returns the string that enables the node factory to identify the
//! node.
/*
    By convention, this string is the name of the node class.
 */
QString %1::type(void)
{
    return "%1";
}

//! Returns the title of the node that appears in the composer GUI.
/*
    The title should indicates the kind of process that it wraps.
 */
QString %1::titleHint(void)
{
    return "%WrappedClass%";
}

//! Returns the name of the input identified by its index \a port.
/*
    
 */
QString %1::inputLabelHint(int port)
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
/*
    
 */
QString %1::outputLabelHint(int port)
{
    /*
    switch (port) {
    case 0:
        return "process";
    case 1:
        return "scalar array";
    default:
        return dtkComposerNodeLeaf::outputLabelHint(port);
    }
    */
}
   
//! Return true if the wrapped process is abstract, that is if there are
//! likely plugins that implement this process.
/*
    
 */
bool %1::isAbstract%2(void) const 
{
    // Uncomment the line you need (Please, erase the other line and
    // this comment ;-) ).

    /* return false; */
    /* return true;  */
}

//! Returns identifier of the wrapped process.
/*
    
 */
QString %1::abstract%2Type(void) const 
{ 
    return "%WrappedClass%"; 
}

//! Executes the logic of the node.
/*
    Firstly, one checks that the required receivers are all connected.
    Secondly, one retrieves the process from these receivers. Thirdly, if
    the wrapped process is abstract, one has to instanciate it using
    following code:

    \code
    if (this->implementationHasChanged())
        d->process = reinterpret_cast<%WrappedClass%*>(this->process());
    \endcode

    After these first steps, one can set the input of the process, update
    it and then set the emitters using process outputs.
 */
void %1::run(void)
{
    //  Here is a sample of what can be the logic of a process node. (You
    //  can erase it of course ;-) !)

    /* 
    if (!d->receiver_index.isEmpty() && !d->receiver_vector.isEmpty() && !d->receiver_process_array.isEmpty()) {

        qlonglong index = *d->receiver_index.process();
        dtkVectorReal *vector = d->receiver_vector.process();
        dtkContainerVector<dtkAbstract%2*> *process_array = d->receiver_process_array.process();

        if (this->implementationHasChanged())
            d->process = reinterpret_cast<%WrappedClass%*>(this->process());

        if (!d->process) {
            dtkWarn() << "no process, abort "<< this->currentImplementation();
            return;
        }

        d->process->setParamater(index, 0);
        
        for (int i = 0; i < vector->size(); ++i)
            d->process->setParamater(*vector[i], i+1);

        
        d->process->set%2(process_array->first());

        d->process->update();

        d->emitter_process.set%2(d->process);
        d->emitter_scalar_array.set%2(reinterpret_cast<dtkContainerVector<qreal> *>(d->process->process()));

    } else {
        dtkWarn() << "The input are not all set. Nothing is done.";
        d->emitter_process.clearData();
        d->emitter_scalar_array.clearData();
        return;
    }
    */
}
