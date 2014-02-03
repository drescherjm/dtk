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
      Here one must declare the inputs of the node using
      dtkComposerTransmitterReceiver<T>, eg:

      \code
      dtkComposerTransmitterReceiver<qlonglong> receiver_index;
      dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;
      dtkComposerTransmitterReceiverVector<dtkAbstractData> receiver_data_array;
      \endcode
    */

public:
    /*
      Here one must declare the outputs of the node using
      dtkComposerTransmitterEmitter<T>, eg:

      \code
      dtkComposerTransmitterEmitter<dtkAbstractData> emitter_data;
      dtkComposerTransmitterEmitterVector<qreal> emitter_scalar_array;
      \endcode
    */

public:
    /*
      Here one must declare the pointer to the data that is wrapped by
      the node. Uncomment the following line if necessary.

      \code
      %WrappedClass% *data;
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
    this->appendReceiver(&(d->receiver_data_array));
    \endcode

    Then the declared emitters must be appended to the current
    node.

    \code
    this->appendEmitter(&(d->emitter_data));
    this->appendEmitter(&(d->emitter_scalar_array));
    \endcode

    Do not forget to set the any pointers to NULL.

    \code
    d->data = NULL;
    \endcode
 */
%NodeName%::%NodeName%(void) : dtkComposerNodeLeafData(), d(new %NodeName%Private)
{

}

//! Node destructor
/*
    If the node is the owner of the wrapped data, one must delete the
    related pointer as follows:

    \code
    if (d->data)
        delete d->data;
    d->data = NULL;
    \endcode
 */
%NodeName%::~%NodeName%(void)
{
    delete d;

    d = NULL;
}

//! Returns the string that enables the node factory to identify the
//! node.
/*
    By convention, this string is the name of the node class.
 */
QString %NodeName%::type(void)
{
    return "%NodeName%";
}

//! Returns the title of the node that appears in the composer GUI.
/*
    The title should indicates the kind of data that it wraps.
 */
QString %NodeName%::titleHint(void)
{
    return "%WrappedClass%";
}

//! Returns the name of the input identified by its index \a port.
/*
    
 */
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
        return "data array";
    default:
        return dtkComposerNodeLeaf::inputLabelHint(port);
    }
    */
}

//! Returns the name of the output identified by its index \a port.
/*
    
 */
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
   
//! Return true if the wrapped data is abstract, that is if there are
//! likely plugins that implement this data.
/*
    
 */
bool %NodeName%::isAbstractData(void) const 
{
    // Uncomment the line you need (Please, erase the other line and
    // this comment ;-) ).

    /* return false; */
    /* return true;  */
}

//! Returns identifier of the wrapped data.
/*
    
 */
QString %NodeName%::abstractDataType(void) const 
{ 
    return "%WrappedClass%"; 
}

//! Executes the logic of the node.
/*
    Firstly, one checks that the required receivers are all connected.
    Secondly, one retrieves the data from these receivers. Thirdly, if
    the wrapped data is abstract, one has to instanciate it using
    following code:

    \code
    if (this->implementationHasChanged())
        d->data = reinterpret_cast<%WrappedClass%*>(this->data());
    \endcode

    After these first steps, one can set the input of the data, update
    it and then set the emitters using data outputs.
 */
void %NodeName%::run(void)
{
    //  Here is a sample of what can be the logic of a data node. (You
    //  can erase it of course ;-) !)

    /* 
    if (!d->receiver_index.isEmpty() && !d->receiver_vector.isEmpty() && !d->receiver_data_array.isEmpty()) {

        qlonglong index = *d->receiver_index.data();
        dtkVectorReal *vector = d->receiver_vector.data();
        dtkContainerVector<dtkAbstractData*> *data_array = d->receiver_data_array.data();

        if (this->implementationHasChanged())
            d->data = reinterpret_cast<%WrappedClass%*>(this->data());

        if (!d->data) {
            dtkWarn() << "no data, abort "<< this->currentImplementation();
            return;
        }

        d->data->setParamater(index, 0);
        
        for (int i = 0; i < vector->size(); ++i)
            d->data->setParamater(*vector[i], i+1);

        
        d->data->setData(data_array->first());

        d->data->update();

        d->emitter_data.setData(d->data);
        d->emitter_scalar_array.setData(reinterpret_cast<dtkContainerVector<qreal> *>(d->data->data()));

    } else {
        dtkWarn() << "The input are not all set. Nothing is done.";
        d->emitter_data.clearData();
        d->emitter_scalar_array.clearData();
        return;
    }
    */
}
