/* dtkPropertyEditor.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: mar. oct. 15 13:03:43 2013 (+0200)
 * Version: 
 * Last-Updated: mar. oct. 15 16:16:22 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 126
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkGuiExport.h"

#include <QFrame>
#include <QVariant>

class dtkPropertyEditorPrivate;

// ///////////////////////////////////////////////////////////////////
// dtkPropertyEditor declaration
// ///////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkPropertyEditor : public QFrame
{
    Q_OBJECT

public:
              dtkPropertyEditor(const QString& property_name, QObject *object, QWidget *parent = 0);
     virtual ~dtkPropertyEditor(void);

public:
    virtual void  setValue(const QVariant& value);
    virtual QVariant value(void) const;

public:
    QObject *propertyObject(void);

public:
    virtual void  setEditorData(const QVariant& data) = 0;
    virtual QVariant editorData(void) = 0;

protected:
    dtkPropertyEditorPrivate *d;
};

// ///////////////////////////////////////////////////////////////////
// dtkPropertyEditorDouble declaration
// ///////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkPropertyEditorDouble : public dtkPropertyEditor
{
    Q_OBJECT

public:
      dtkPropertyEditorDouble(const QString& property_name, QObject *object, QWidget *parent = 0);
     ~dtkPropertyEditorDouble(void);

public:
    void  setEditorData(const QVariant& data);
    QVariant editorData(void);

public slots:
    void onValueChanged(double value);
};

// ///////////////////////////////////////////////////////////////////
// dtkPropertyEditorInteger declaration
// ///////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkPropertyEditorInteger : public dtkPropertyEditor
{
    Q_OBJECT

public:
      dtkPropertyEditorInteger(const QString& property_name, QObject *object, QWidget *parent = 0);
     ~dtkPropertyEditorInteger(void);

public:
    void  setEditorData(const QVariant& data);
    QVariant editorData(void);

public slots:
    void onValueChanged(int value);
};

// ///////////////////////////////////////////////////////////////////
// dtkPropertyEditorString declaration
// ///////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkPropertyEditorString : public dtkPropertyEditor
{
    Q_OBJECT

public:
      dtkPropertyEditorString(const QString& property_name, QObject *object, QWidget *parent = 0);
     ~dtkPropertyEditorString(void);

public:
    void  setEditorData(const QVariant& data);
    QVariant editorData(void);

public slots:
    void onTextChanged(const QString& text);
};

// ///////////////////////////////////////////////////////////////////
// dtkPropertyEditorEnum declaration
// ///////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkPropertyEditorEnum : public dtkPropertyEditor
{
    Q_OBJECT

public:
      dtkPropertyEditorEnum(const QString& property_name, QObject *object, QWidget *parent = 0);
     ~dtkPropertyEditorEnum(void);

public:
    void  setEditorData(const QVariant& data);
    QVariant editorData(void);

public slots:
    void onIndexChanged(int index);
};

