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

#pragma once

#include <QtCore>

#include "dtkWidgetsExport.h"

class QWidget;

// ///////////////////////////////////////////////////////////////////
// Widget Definition
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_WIDGET_CLASS(type, Export)            \
    class Export type##Widget : public QWidget            \
    {                                                     \
	public:                                               \
        type##Widget(QWidget *parent) : QWidget(parent) { \
                                                          \
        }                                                 \
                                                          \
	public:                                               \
        virtual void setProcess(type *process) = 0;       \
    };

// ///////////////////////////////////////////////////////////////////
// Trait definition
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkWidgetTrait {};

#define DTK_DECLARE_WIDGET_TRAIT(type)          \
    template <> class dtkWidgetTrait<type>      \
    {                                           \
    public:                                     \
        typedef type##Widget WidgetType;        \
    };

// ///////////////////////////////////////////////////////////////////
// dtkWidgetFactory
// ///////////////////////////////////////////////////////////////////

template <typename T> class DTKWIDGETS_EXPORT dtkWidgetFactory : public QObject
{
public:
     dtkWidgetFactory(void);
    ~dtkWidgetFactory(void);

public:
    typedef typename dtkWidgetTrait<T>::WidgetType *(*creator) ();

public:
    void record(const QString& key, creator widget);

public:
    typename dtkWidgetTrait<T>::WidgetType *get(const QString& key, T *process);

public:
    QStringList keys(void) const;

private:
    QHash<QString, creator> m_widgets;
    QHash<T * , typename dtkWidgetTrait<T>::WidgetType *> m_instanciated;
};

#include "dtkWidgetFactory.tpp"

#define DTK_ASSOCIATE_WIDGET(type, Export) \
    DTK_DECLARE_WIDGET_CLASS(type, Export);\
    DTK_DECLARE_WIDGET_TRAIT(type);

//
// dtkWidgetFactory.h ends here
