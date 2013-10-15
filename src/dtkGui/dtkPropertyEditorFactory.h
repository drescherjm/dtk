/* dtkPropertyEditorFactory.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: mar. oct. 15 10:21:29 2013 (+0200)
 * Version: 
 * Last-Updated: mar. oct. 15 16:23:26 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 52
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkGuiExport.h"

#include <QObject>

class dtkPropertyEditor;
class dtkPropertyEditorFactoryPrivate;

// ///////////////////////////////////////////////////////////////////
// dtkPropertyEditorFactory declaration
// ///////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkPropertyEditorFactory : public QObject
{
    Q_OBJECT

public:
    typedef dtkPropertyEditor *(*dtkPropertyEditorCreator)(const QString&, QObject*, QWidget*);

public:
    static dtkPropertyEditorFactory *instance(void);

public:
    bool registerCreator(int type, dtkPropertyEditorCreator func);

public slots:
    dtkPropertyEditor *create(const QString& property_name, QObject *object, QWidget *parent = 0);

protected:
     dtkPropertyEditorFactory(void);
    ~dtkPropertyEditorFactory(void);

private:    
    static dtkPropertyEditorFactory *s_instance;

private:
    dtkPropertyEditorFactoryPrivate *d;

private slots:
    void clear(void) { delete this; }
};
