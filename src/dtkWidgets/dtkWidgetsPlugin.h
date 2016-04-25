/* @(#)dtkWidgetsPlugin.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/04/25 13:00:33
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkCoreWidgetFactory.h"

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_WIDGET_FACTORY
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_WIDGET_FACTORY(type,Export)                              \
    class Export type##WidgetFactory : public dtkCoreWidgetFactory{}; \
    template <typename T> QWidget *type##WidgetCreator() { return new T; };



