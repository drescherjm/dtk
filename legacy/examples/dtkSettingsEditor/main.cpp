/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Dec 23 09:58:27 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec 23 10:17:17 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkGui/dtkSettingsEditor.h>

#include <QtGui>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    QScopedPointer<dtkSettingsEditor> editor(new dtkSettingsEditor);
    editor->setSettings("inria", "dtk");
    editor->show();

    return application.exec();
}
