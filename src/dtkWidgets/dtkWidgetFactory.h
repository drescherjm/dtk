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
// dtkWidgetFactory
// ///////////////////////////////////////////////////////////////////

class DTKWIDGETS_EXPORT dtkWidgetFactory : public QObject
{
public:
     dtkWidgetFactory(void);
    ~dtkWidgetFactory(void);

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
// dtkWidgetFactory.h ends here
