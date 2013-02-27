/* dtkDistributedItem.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Wed Feb 27 23:11:32 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainerItem interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkDistributedContainerItem
{
public:
    virtual ~dtkDistributedContainerItem(void) {;}

public:
    virtual void assign(const T& value) = 0;

    virtual void increment(const T& value) = 0;
    virtual void decrement(const T& value) = 0;

    virtual void multiply(const T& value) = 0;
    virtual void   divide(const T& value) = 0;

public:
    virtual T value(void) const = 0;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedItem interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkDistributedItem
{
public:
    inline dtkDistributedItem(dtkDistributedContainerItem<T> *d_ptr);

public:
    inline ~dtkDistributedItem(void);

public:
    inline dtkDistributedItem& operator = (const T& value);

    inline dtkDistributedItem& operator += (const T& value);
    inline dtkDistributedItem& operator -= (const T& value);
    inline dtkDistributedItem& operator *= (const T& value);
    inline dtkDistributedItem& operator /= (const T& value);

public:
    inline T value(void) const;

private:
    dtkDistributedContainerItem<T> *d;

private:
    friend class dtkDistributedArray<T>;

};

// /////////////////////////////////////////////////////////////////

template <typename T> dtkDistributedItem<T>::dtkDistributedItem(dtkDistributedContainerItem<T> *d_ptr) : d(d_ptr)
{

}

template <typename T> dtkDistributedItem<T>::~dtkDistributedItem(void)
{
    if (d) {
        delete d;
    }
    d = NULL;
}

template <typename T> dtkDistributedItem<T>& dtkDistributedItem<T>::operator = (const T& value)
{
    d->assign(value);
    return (*this);
}

template <typename T> dtkDistributedItem<T>& dtkDistributedItem<T>::operator += (const T& value)
{
    d->increment(value);
    return (*this);
}

template <typename T> dtkDistributedItem<T>& dtkDistributedItem<T>::operator -= (const T& value)
{
    d->decrement(value);
    return (*this);
}

template <typename T> dtkDistributedItem<T>& dtkDistributedItem<T>::operator *= (const T& value)
{
    d->multiply(value);
    return (*this);
}

template <typename T> dtkDistributedItem<T>& dtkDistributedItem<T>::operator /= (const T& value)
{
    d->divide(value);
    return (*this);
}

template <typename T> T dtkDistributedItem<T>::value(void) const
{
    return d->value();
}
