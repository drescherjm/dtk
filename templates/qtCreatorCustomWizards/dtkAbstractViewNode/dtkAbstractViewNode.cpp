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
      dtkComposerTransmitterReceiverVector<dtkAbstractView> receiver_view_array;
      \endcode
    */

public:
    /*
      Here one must declare the outputs of the node using
      dtkComposerTransmitterEmitter<T>, eg:

      \code
      dtkComposerTransmitterEmitter<dtkAbstractView> emitter_view;
      dtkComposerTransmitterEmitterVector<qreal> emitter_scalar_array;
      \endcode
    */

public:
    /*
      Here one must declare the pointer to the view that is wrapped by
      the node. Uncomment the following line if necessary.

      \code
      %WrappedClass% *view;
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
    this->appendReceiver(&(d->receiver_view_array));
    \endcode

    Then the declared emitters must be appended to the current
    node.

    \code
    this->appendEmitter(&(d->emitter_view));
    this->appendEmitter(&(d->emitter_scalar_array));
    \endcode

    Do not forget to set the any pointers to NULL.

    \code
    d->view = NULL;
    \endcode
 */
%NodeName%::%NodeName%(void) : dtkComposerNodeLeafView(), d(new %NodeName%Private)
{

}

//! Node destructor
/*
    If the node is the owner of the wrapped view, one must delete the
    related pointer as follows:

    \code
    if (d->view)
        delete d->view;
    d->view = NULL;
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
    The title should indicates the kind of view that it wraps.
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
        return "view array";
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
        return "view";
    case 1:
        return "scalar array";
    default:
        return dtkComposerNodeLeaf::outputLabelHint(port);
    }
    */
}
   
//! Return true if the wrapped view is abstract, that is if there are
//! likely plugins that implement this view.
/*
    
 */
bool %NodeName%::isAbstractView(void) const 
{
    // Uncomment the line you need (Please, erase the other line and
    // this comment ;-) ).

    /* return false; */
    /* return true;  */
}

//! Returns identifier of the wrapped view.
/*
    
 */
QString %NodeName%::abstractViewType(void) const 
{ 
    return "%WrappedClass%"; 
}

//! Executes the logic of the node.
/*
    Firstly, one checks that the required receivers are all connected.
    Secondly, one retrieves the view from these receivers. Thirdly, if
    the wrapped view is abstract, one has to instanciate it using
    following code:

    \code
    if (this->implementationHasChanged())
        d->view = reinterpret_cast<%WrappedClass%*>(this->view());
    \endcode

    After these first steps, one can set the input of the view, update
    it and then set the emitters using view outputs.
 */
void %NodeName%::run(void)
{
    //  Here is a sample of what can be the logic of a view node. (You
    //  can erase it of course ;-) !)

    /* 
    if (!d->receiver_index.isEmpty() && !d->receiver_vector.isEmpty() && !d->receiver_view_array.isEmpty()) {

        qlonglong index = *d->receiver_index.view();
        dtkVectorReal *vector = d->receiver_vector.view();
        dtkContainerVector<dtkAbstractView*> *view_array = d->receiver_view_array.view();

        if (this->implementationHasChanged())
            d->view = reinterpret_cast<%WrappedClass%*>(this->view());

        if (!d->view) {
            dtkWarn() << "no view, abort "<< this->currentImplementation();
            return;
        }

        d->view->setParamater(index, 0);
        
        for (int i = 0; i < vector->size(); ++i)
            d->view->setParamater(*vector[i], i+1);

        
        d->view->setView(view_array->first());

        d->view->update();

        d->emitter_view.setView(d->view);
        d->emitter_scalar_array.setView(reinterpret_cast<dtkContainerVector<qreal> *>(d->view->view()));

    } else {
        dtkWarn() << "The input are not all set. Nothing is done.";
        d->emitter_view.clearData();
        d->emitter_scalar_array.clearData();
        return;
    }
    */
}
