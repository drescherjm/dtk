#ifndef DTKSMARTPOINTER_H
#define DTKSMARTPOINTER_H

#include <QHash>

class dtkAbstractFactory;

/**
 * A Smart pointer for automatic reference counting of anything derived from dtkAbstractObject. 
 * 
 */
template< class T > class dtkSmartPointer {
public:
    typedef T ObjectType;

    /** Constructor  */
    dtkSmartPointer() : d(0) { }

    /** Copy constructor  */
    dtkSmartPointer( const dtkSmartPointer<T>& p) :
        d(p.d)
    { this->retain(); }

    /** Constructor to pointer p  */
    dtkSmartPointer (T* p) :
        d(p)
    { this->retain(); }

    /** Destructor  */
    ~dtkSmartPointer ()
    {
        this->release();
        d = 0;
    }

    /** Overload operator ->  */
    T* operator->() const
    { return d; }

    /** Return pointer to object.  */
    operator T* () const
    { return d; }

    /** Test if the pointer has been initialized */
    bool isNull() const
    { return d == 0; }

    /** Template comparison operators. */
    template <typename TR>
    bool operator == ( TR r ) const
    { return (d == static_cast<const T*>(r) ); }

    template <typename TR>
    bool operator != ( TR r ) const
    { return (d != static_cast<const T*>(r) ); }

    /* Operators allow the pointer to be used in containers */
    bool operator==( const dtkSmartPointer& r ) const
        { return d == r.d; }
    bool operator!=( const dtkSmartPointer& r ) const
        { return d != r.d; }
    bool operator<( const dtkSmartPointer& r ) const
        { return d < r.d; }
    bool operator<=( const dtkSmartPointer& r ) const
        { return d <= r.d; }
    bool operator>( const dtkSmartPointer& r ) const
        { return d > r.d; }
    bool operator>=( const dtkSmartPointer& r ) const
        { return d >= r.d; }

    /** Access functions to pointer. */
    T* data()
    { return d; }

    const T* constData() const
    { return d; }

    T& operator*()
    { return *d; }

    const T& operator*() const
    { return *d; }

    /** Overload operator assignment.  */
    dtkSmartPointer& operator=(const dtkSmartPointer& r)
    { return this->operator=(r.d); }

    /** Overload operator assignment.  */
    dtkSmartPointer &operator = (T* r)
    {
        if (d != r)
        {
            T* tmp = d; //avoid recursive unregisters by retaining temporarily
            d = r;
            this->retain();
            if ( tmp ) { tmp->release(); }
        }
        return *this;
    }

    //! Swap this instance's shared data pointer with the shared data pointer in other
    void swap( dtkSmartPointer& other)
    {
        T* tmp = d;
        d = other.d;
        other.d = tmp;
    }

    /** Assign without incrementing reference count of assigned object.  */
    dtkSmartPointer& takePointer(T*r)
    {
        if (d != r)
        {
            T* tmp = d; //avoid recursive unregisters by retaining temporarily
            d = r;
            if ( tmp ) { tmp->release(); }
        }
        return *this;
    }

    /** Release the pointer without decreasing the reference count.*/
    T* releasePointer()
    {
        T* tmp = d;
        d = 0;
        return tmp;
    }

private:
    /** The pointer to the object referred to by this smart pointer. */
    T* d;

    void retain()
    {
        if(d) { d->retain(); }
    }

    void release()
    {
        if(d) { d->release(); }
    }
};

template <class T>
inline uint qHash(const dtkSmartPointer<T>& key) { return qHash(key.constData()); }

#endif // DTKSMARTPOINTER_H
