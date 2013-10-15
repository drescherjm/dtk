/* dtkObjectEditor.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: mar. oct. 15 16:54:54 2013 (+0200)
 * Version: 
 * Last-Updated: mar. oct. 15 17:01:48 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 17
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkGuiExport.h"

#include <QScrollArea>

class dtkObjectEditorPrivate;

class DTKGUI_EXPORT dtkObjectEditor : public QScrollArea
{
    Q_OBJECT

public:
     dtkObjectEditor(QObject *object, QWidget *parent = 0);
    ~dtkObjectEditor(void);

private:
    dtkObjectEditorPrivate *d;
};
