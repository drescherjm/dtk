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

#include "dtkComposerNodeLeafProcessSupport.h"

#include <dtkCoreSupport/dtkAbstractProcessFactory.h>
#include <dtkMeta>

// ///////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafProcessSupport implementation
// ///////////////////////////////////////////////////////////////////

dtkComposerNodeObject<dtkAbstractProcess>::dtkComposerNodeObject(void) : dtkComposerNodeLeafObject(), m_implementation(QString()), m_process(0)
{

}

dtkComposerNodeObject<dtkAbstractProcess>::~dtkComposerNodeObject(void)
{
    if (m_process)
        delete m_process;

    m_process = 0;
}

QVariant dtkComposerNodeObject<dtkAbstractProcess>::variant(void) const
{
    if (this->object())
        return dtkMetaType::variantFromValue(this->object());
    else
        return QVariant();
}

dtkAbstractProcess *dtkComposerNodeObject<dtkAbstractProcess>::object(void) const
{
    return this->process();
}

bool dtkComposerNodeObject<dtkAbstractProcess>::createObject(const QString& implementation)
{
    if (implementation.isEmpty() || implementation == "Choose implementation")
        return false;

    if (implementation == "default")
        const_cast<QString&>(implementation) = this->abstractProcessType();

    if (!this->process()) {
        this->setProcess(dtkAbstractProcessFactory::instance()->create(implementation));

    } else if (this->process()->identifier() != implementation) {
        this->setProcess(dtkAbstractProcessFactory::instance()->create(implementation));
    }

    if (m_process != this->process()) {
        if (m_process) {
            delete m_process;
        }

        m_process = this->process();

        if (m_process)
            m_implementation = this->process()->identifier();
    }

    return (m_process != NULL);
}

QStringList dtkComposerNodeObject<dtkAbstractProcess>::implementations(void) const
{
    QStringList implementations = dtkAbstractProcessFactory::instance()->implementations(this->abstractProcessType());

    if (this->enableDefaultImplementation())
        implementations.prepend("default");

    return implementations;
}

QString dtkComposerNodeObject<dtkAbstractProcess>::currentImplementation(void) const
{
    return m_implementation;
}

bool dtkComposerNodeObject<dtkAbstractProcess>::implementationHasChanged(const QString& implementation) const
{
    return (m_implementation != implementation);
}

bool dtkComposerNodeObject<dtkAbstractProcess>::enableDefaultImplementation(void) const
{
    return false;
}

bool dtkComposerNodeObject<dtkAbstractProcess>::isInteractive(void)
{
    return false;
}

void dtkComposerNodeObject<dtkAbstractProcess>::clearProcess(void)
{
    dtkAbstractProcess *p = this->process();

    if (p)
        delete p;

    this->setProcess(NULL);
}

//
// dtkComposerNodeLeafProcessSupport.cpp ends here
