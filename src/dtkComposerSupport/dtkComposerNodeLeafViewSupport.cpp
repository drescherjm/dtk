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

#include "dtkComposerNodeLeafViewSupport.h"

#include <dtkCoreSupport/dtkAbstractViewFactory.h>
#include <dtkMeta>

// ///////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafViewSupport implementation
// ///////////////////////////////////////////////////////////////////

dtkComposerNodeObject<dtkAbstractView>::dtkComposerNodeObject(void) : dtkComposerNodeLeafObject(), m_implementation_has_changed(false), m_view(0)
{
    
}

dtkComposerNodeObject<dtkAbstractView>::~dtkComposerNodeObject(void)
{
    if (m_view)
        delete m_view;

    m_view = 0;
}
QVariant dtkComposerNodeObject<dtkAbstractView>::variant(void) const
{
    if (this->object())
        return dtkMetaType::variantFromValue(this->object());
    else
        return QVariant();
}

dtkAbstractView *dtkComposerNodeObject<dtkAbstractView>::object(void) const
{
    return const_cast<dtkComposerNodeObject<dtkAbstractView> *>(this)->view();
}

bool dtkComposerNodeObject<dtkAbstractView>::createObject(const QString& implementation)
{ 
    m_implementation_has_changed = false;

    if (implementation.isEmpty() || implementation == "Choose implementation")
        return false;

    if (implementation == "default")
        const_cast<QString&>(implementation) = this->abstractViewType();
        
    if (!m_view) {
        m_view = dtkAbstractViewFactory::instance()->create(implementation);
        m_implementation_has_changed = true;

    } else if (m_view->identifier() != implementation) {
        delete m_view;
        m_view = dtkAbstractViewFactory::instance()->create(implementation);
        m_implementation_has_changed = true;
    }

    return (m_view != NULL);
}

QImage dtkComposerNodeObject<dtkAbstractView>::screenshot(void) const
{
    QWidget *widget = m_view->widget();
    QPixmap pixmap(widget->size());
    widget->render(&pixmap);
    if( pixmap.width() > 1920) {
        // limit width to FULL HD res.
        return pixmap.scaledToWidth(1920).toImage();
    }

    return pixmap.toImage();

}

void dtkComposerNodeObject<dtkAbstractView>::setView(dtkAbstractView *view)
{
    m_view = view;
}

dtkAbstractView *dtkComposerNodeObject<dtkAbstractView>::view(void)
{
    return m_view;
}

QStringList dtkComposerNodeObject<dtkAbstractView>::implementations(void) const
{
    QStringList implementations = dtkAbstractViewFactory::instance()->implementations(this->abstractViewType());
    
    if (this->enableDefaultImplementation())
        implementations.prepend("default");

    return implementations;
}

QString dtkComposerNodeObject<dtkAbstractView>::currentImplementation(void) const
{
    if (m_view)
        return m_view->identifier();

    return QString();
}

bool dtkComposerNodeObject<dtkAbstractView>::implementationHasChanged(void) const
{
    return (m_implementation_has_changed);
}

bool dtkComposerNodeObject<dtkAbstractView>::implementationHasChanged(const QString& implementation) const
{
    if (m_view)
        return (m_view->identifier() != implementation);

    return true;
}

bool dtkComposerNodeObject<dtkAbstractView>::enableDefaultImplementation(void) const
{
    return false;
}

// 
// dtkComposerNodeLeafViewSupport.cpp ends here


// 
// dtkComposerNodeLeafViewSupport.cpp ends here
