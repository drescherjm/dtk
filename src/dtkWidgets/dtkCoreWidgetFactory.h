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
// dtkCoreWidgetFactory
// ///////////////////////////////////////////////////////////////////

class DTKWIDGETS_EXPORT dtkCoreWidgetFactory : public QObject
{
public:
     dtkCoreWidgetFactory(void);
    ~dtkCoreWidgetFactory(void);

public:
    void record(const QString& key, QWidget* widget);

public:
    QWidget *get(const QString& key) const;

public:
    QStringList keys(void) const;

private:
    QHash<QString, QWidget*> widgets;
};

//
// dtkCoreWidgetFactory.h ends here
