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

#include "dtkWidgetFactory.h"

template <typename T> dtkWidgetFactory<T>::dtkWidgetFactory(void)
{

}

template <typename T>  dtkWidgetFactory<T>::~dtkWidgetFactory(void)
{

}

// /////////////////////////////////////////////////////////////////
// Type creator registration
// /////////////////////////////////////////////////////////////////

template <typename T>  void dtkWidgetFactory<T>::record(const QString& key, creator widget)
{
    if (this->m_widgets.contains(key)) {
        qDebug() << Q_FUNC_INFO << "Factory already contains key" << key << ". Nothing is done";
        return;
    }

    this->m_widgets.insert(key, widget);
}

// /////////////////////////////////////////////////////////////////
// Type creator invokation
// /////////////////////////////////////////////////////////////////

template <typename T> typename dtkWidgetTrait<T>::WidgetType *dtkWidgetFactory<T>::get(const QString& key, T* process)
{
    if(!this->m_widgets.contains(key))
        return NULL;
        
    if(!m_instanciated.contains(process)) {
      this->m_instanciated.insert(process,this->m_widgets.value(key)());
    }
    
    return this->m_instanciated.value(process);
}

// /////////////////////////////////////////////////////////////////
// Type creator inspection
// /////////////////////////////////////////////////////////////////

template <typename T>  QStringList dtkWidgetFactory<T>::keys(void) const
{
    return this->m_widgets.keys();
}

//
// dtkWidgetFactory_t.h ends here
