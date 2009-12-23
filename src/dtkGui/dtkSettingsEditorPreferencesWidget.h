/* dtkSettingsEditorPreferencesWidget.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Dec 23 10:31:38 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec 23 10:36:27 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSETTINGSEDITORPREFERENCESWIDGET_H
#define DTKSETTINGSEDITORPREFERENCESWIDGET_H

#include "dtkGuiExport.h"
#include "dtkPreferencesWidget.h"

#include <QtCore>
#include <QtGui>

class dtkSettingsEditorPreferencesWidgetPrivate;

class DTKGUI_EXPORT dtkSettingsEditorPreferencesWidget : public dtkPreferencesPage
{
    Q_OBJECT

public:
     dtkSettingsEditorPreferencesWidget(QWidget *parent);
    ~dtkSettingsEditorPreferencesWidget(void);

signals:
    void accepted(void);
    void rejected(void);

private:
    dtkSettingsEditorPreferencesWidgetPrivate *d;
};

#endif
