/* dtkComposerVariant.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Mar 20 12:49:18 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 20 14:13:55 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 32
 */

/* Change Log:
 * 
 */

#pragma once

#ifndef DTKVARIANT_H
#define DTKVARIANT_H

#include <QtCore>
#include <QtGui>

template <typename T, bool U> class dtkComposerVariantHandler;

// ///////////////////////////////////////////////////////////////////
// Compat classes for porting purposes only
// ///////////////////////////////////////////////////////////////////

class dtkAbstractObject : public QObject
{
    Q_OBJECT

public:
     dtkAbstractObject(void) {}
    ~dtkAbstractObject(void) {}

public:
    QString description(void) {
	return QString();
    }

    QString identifier(void) {
	return QString();
    }
};

class dtkAbstractData : public dtkAbstractObject
{

};

template <typename T> class dtkMatrix : public dtkAbstractObject
{

};

typedef dtkMatrix<qreal> dtkMatrixReal;

// /////////////////////////////////////////////////////////////////
// dtkComposerVariant interface
// /////////////////////////////////////////////////////////////////

class dtkComposerVariant : public QVariant
{
public:
     dtkComposerVariant(void);
     dtkComposerVariant(const dtkComposerVariant& other);
    ~dtkComposerVariant(void);

public:
    dtkComposerVariant& operator = (const dtkComposerVariant& other);

public:
    bool operator == (const dtkComposerVariant& other);
    bool operator != (const dtkComposerVariant& other);

public:
    QString  identifier(void) const;
    QString description(void) const;

public:
    void clear(void);

public:
    template<typename T> bool canConvert(void) const;

public:
    bool isValid(void) const;
    bool  isNull(void) const;

public:
    bool  isAbstractObject(void) const;
    bool    isAbstractData(void) const;
    bool      isMatrixReal(void) const;

    dtkAbstractObject *toAbstractObject(void) const;
    dtkAbstractData     *toAbstractData(void) const;
    dtkMatrix<double>     *toMatrixReal(void) const;

    QByteArray toByteArray(void) const;

public:
    template<typename T> void setValue(const T& value);

    template<typename T> T value(void) const;

public:
    void swap(dtkComposerVariant& other);

public:
    static dtkComposerVariant fromQVariant(const QVariant& variant);

private:
    dtkComposerVariant(const QVariant& variant);

private:
    dtkAbstractObject *m_object;
    dtkAbstractData   *m_data;
    dtkMatrix<double> *m_matrix;

public:
    template<typename T, bool> friend class dtkComposerVariantHandler;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerVariant implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerVariant.tpp"

#endif
