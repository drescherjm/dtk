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

#include "dtkDistributedContainer.h"

/*!
  \class dtkDistributedContainer
  \inmodule dtkDistributed
  \brief The dtkDistributedContainer class is the base class for any distributed container.

  dtkDistributedContainer contains all the required data for a
  distributed container, namely its global size, the mapper that
  describes how the data are distributed across all the process units
  and the communicator.
*/


/*! \fn dtkDistributedContainer::dtkDistributedContainer(void)

  Constructs a distributed container and instanciates a default mapper.

*/

/*! \fn dtkDistributedContainer::dtkDistributedContainer(const qlonglong& size)

  Constructs a distributed container of size \a size and instanciates a default mapper.

*/

/*! \fn dtkDistributedContainer::dtkDistributedContainer(const qlonglong& size, dtkDistributedMapper *mapper)

  Constructs a distributed container of size \a size and with the custom mapper \a mapper.

  \sa setMapper
*/

/*! \fn virtual dtkDistributedContainer::~dtkDistributedContainer(void)

  Destroys the distributed container.

*/

/*! \fn void dtkDistributedContainer::setMapper(dtkDistributedMapper *mapper)

  Sets the custom mapper \a mapper.

*/

/*! \fn bool dtkDistributedContainer::empty(void) const

  Returns \c true if the distributed container has size 0; otherwise returns \c false.

  \sa size()

*/

/*! \fn qlonglong dtkDistributedContainer::size(void) const

  Returns the number of items in the distributed container.

  \sa empty()

*/

/*! \fn dtkDistributedMapper *dtkDistributedContainer::mapper(void) const

  Returns the mapper.

*/

/*! \fn dtkDistributedCommunicator *dtkDistributedContainer::communicator(void) const

  Returns the communicator.

*/

/*! \fn qlonglong dtkDistributedContainer::wid(void) const

  Returns the current worker id.

*/

//
// dtkDistributedContainer.cpp ends here
