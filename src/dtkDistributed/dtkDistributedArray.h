/* dtkDistributedArray.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Fri Mar  8 15:06:15 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar  8 16:08:12 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 25
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkDistributedMapper.h"
#include "dtkDistributedWorker.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer
// /////////////////////////////////////////////////////////////////

class dtkDistributedContainer
{
public:
    virtual ~dtkDistributedContainer(void) {}

public:
    virtual void setMode(const dtkDistributed::Mode& mode) = 0;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedArray
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArray : public dtkDistributedContainer
{
public:
    class item;
    class iterator;

public:
     inline  dtkDistributedArray(const qlonglong& count, dtkDistributedWorker *worker);
     inline ~dtkDistributedArray(void);

#pragma mark -
#pragma mark Handler nested class

public:
     class handler
     {
     protected:
         friend class dtkDistributedArray<T>;

     protected:
         qlonglong buffer_count;

     protected:
         T *buffer;

     public:
         inline          handler(dtkDistributedArray<T>& array) : buffer(0), buffer_count(0) {;}
         inline virtual ~handler(void) {}

     public:
         inline virtual bool      empty(void) const { return !buffer_count; }
         inline virtual qlonglong count(void) const { return  buffer_count; }
         inline virtual void      setAt(const qlonglong& index, const T& value) { buffer[index] = value; }
         inline virtual T            at(const qlonglong& index) const { return buffer[index]; }
         inline virtual T         first(void) const { return buffer[0]; }
         inline virtual T          last(void) const { return buffer[buffer_count-1]; }
     };
     friend class handler;

#pragma mark -
#pragma mark Handler nested class - global variation

private:
     class global_handler : public handler
     {
         friend class dtkDistributedArray<T>;
         using dtkDistributedArray<T>::handler::buffer;
         dtkDistributedMapper       *m_mapper;
         dtkDistributedCommunicator *m_comm;
         qlonglong m_count;
         qlonglong m_wid;
         qlonglong buffer_id;

     public:
          global_handler(dtkDistributedArray<T>& array) : handler(array) {;}
         ~global_handler(void) {;}

     public:
         inline bool      empty(void) const { return !m_count; }
         inline qlonglong count(void) const { return  m_count; }
         inline void      setAt(const qlonglong& index, const T& value) 
	 { 
	     qint32 owner = static_cast<qint32>(m_mapper->owner(index));
	     qlonglong pos = m_mapper->globalToLocal(index);
	     m_comm->put(owner, pos, &(const_cast<T&>(value)), buffer_id);
	 }
         inline T at(const qlonglong& index) const 
	 { 
	     qint32 owner  = static_cast<qint32>(m_mapper->owner(index));
	     qlonglong pos = m_mapper->globalToLocal(index);
	     if (m_wid == owner) {
                     return buffer[pos];
	     } else {
		 T temp;
		 m_comm->get(owner, pos, &temp, buffer_id);
		 return temp;
	     }
	 }
         inline T first(void) const { return this->at(0); }
         inline T  last(void) const { return this->at(m_count-1); }
     };
     friend class global_handler;

#pragma mark -
#pragma mark Item nested class

public:
    class item
    {
        friend class dtkDistributedArray<T>::iterator;
        dtkDistributedArray<T>::handler *h;
        qlonglong id;

    public:
        inline  item(void) : h(0), id(0) {;}
        inline  item(dtkDistributedArray<T>::handler *handler, const qlonglong& index) : h(handler), id(index) {;}
        inline  item(const item& o) : h(o.h), id(o.id) {;}
        inline ~item(void) {;}

    public:
        inline item& operator = (const item& o) { h = o.h; id = o.id; return *this; }  

    public:
        inline T operator * (void) const { return h->at(id); }
        inline item& operator =  (const T& value) { h->setAt(id, value);             return *this; }
        inline item& operator += (const T& value) { h->setAt(id, h->at(id) + value); return *this; }
        inline item& operator -= (const T& value) { h->setAt(id, h->at(id) - value); return *this; }
        inline item& operator *= (const T& value) { h->setAt(id, h->at(id) * value); return *this; }
        inline item& operator /= (const T& value) { h->setAt(id, h->at(id) / value); return *this; }
        inline bool  operator == (const item &o) const { return id == o.id; }
        inline bool  operator != (const item &o) const { return id != o.id; }
        inline bool  operator <  (const item &o) const { return id  < o.id; }
        inline bool  operator >  (const item &o) const { return id  > o.id; }
        inline bool  operator <= (const item &o) const { return id <= o.id; }
        inline bool  operator >= (const item &o) const { return id >= o.id; }

    private:
        item& operator ++ (void) { ++id; return *this; }
        item& operator -- (void) { --id; return *this; }
        item  operator ++ (int)  { ++id; return item(h, id-1); }
        item  operator -- (int)  { --id; return item(h, id+1); }
    };
    friend class item;

#pragma mark -
#pragma mark Iterator nested class

    class iterator 
    {
        friend class const_iterator;
        item it;

    public:
        inline  iterator(void) : it(item()) {;}
        inline  iterator(dtkDistributedArray<T>::handler *handler, const qlonglong& index = 0) : it(handler, index) {;}
        inline  iterator(const iterator& o) : it(o.it) {;}
        inline ~iterator(void) {;}

    public:
        inline iterator& operator = (const iterator& o) { it = o.it; }

    public:
        inline item operator *  (void)        const { return it; }
        inline item operator [] (qlonglong j) const { return item(it.h, it.id + j); }
        inline bool operator == (const iterator &o) const { return it == o.it; }
        inline bool operator != (const iterator &o) const { return it != o.it; }
        inline bool operator <  (const iterator &o) const { return it  < o.it; }
        inline bool operator >  (const iterator &o) const { return it  > o.it; }
        inline bool operator <= (const iterator &o) const { return it <= o.it; }
        inline bool operator >= (const iterator &o) const { return it >= o.it; }
        inline iterator& operator ++ (void) { ++it; return *this; }
        inline iterator  operator ++ (int)  { ++it; return iterator(it.h, it.id-1); }
        inline iterator& operator -- (void) { --it; return *this; }
        inline iterator  operator -- (int)  { --it; return iterator(it.h, it.id+1); }
        inline iterator& operator += (qlonglong j) { it.id += j; return *this; }
        inline iterator& operator -= (qlonglong j) { it.id -= j; return *this; }
        inline iterator  operator +  (qlonglong j) const { return iterator(it.h, it.id + j); }
        inline iterator  operator -  (qlonglong j) const { return iterator(it.h, it.id - j); }
        inline qlonglong operator -  (const iterator& o) const { return it.id - o.it.id; }
    };
    friend class iterator;

#pragma mark -
#pragma mark Iterator nested class - const variation

public:
    class const_iterator 
    {
        const dtkDistributedArray<T>::handler *h;
        qlonglong id;

    public:
                 inline const_iterator(void) : h(0), id(0) {;}
                 inline const_iterator(const dtkDistributedArray<T>::handler *handler, const qlonglong& index = 0) : h(handler), id(index) {;}
                 inline const_iterator(const const_iterator& o) : h(o.h), id(o.id) {;}
        explicit inline const_iterator(const iterator& o) : h(o.h), id(o.id) {;}
        inline         ~const_iterator(void) {;}

    public:
        inline const_iterator& operator = (const const_iterator& o) { h = o.h; id = o.id; }

    public:
        inline T operator *  (void)        const { return h->at(id); }
        inline T operator [] (qlonglong j) const { return h->at(id + j); }
        inline bool operator == (const const_iterator &o) const { return id == o.id; }
        inline bool operator != (const const_iterator &o) const { return id != o.id; }
        inline bool operator <  (const const_iterator &o) const { return id  < o.id; }
        inline bool operator >  (const const_iterator &o) const { return id  > o.id; }
        inline bool operator <= (const const_iterator &o) const { return id <= o.id; }
        inline bool operator >= (const const_iterator &o) const { return id >= o.id; }
        inline const_iterator& operator ++ (void) { ++id; return *this; }
        inline const_iterator  operator ++ (int)  { ++id; return const_iterator(h, id-1); }
        inline const_iterator& operator -- (void) { --id; return *this; }
        inline const_iterator  operator -- (int)  { --id; return const_iterator(h, id+1); }
        inline const_iterator& operator += (qlonglong j) { id += j; return *this; }
        inline const_iterator& operator -= (qlonglong j) { id -= j; return *this; }
        inline const_iterator  operator +  (qlonglong j) const { return const_iterator(h, id + j); }
        inline const_iterator  operator -  (qlonglong j) const { return const_iterator(h, id - j); }
        inline qlonglong       operator -  (const const_iterator& o) const { return id - o.id; }
    };
    friend class const_iterator;

private:
    void initialize(void);

public:
    inline void setMode(const dtkDistributed::Mode& mode);
    
public:
    inline bool        empty(void) const { return m_handler->empty(); }
    inline qlonglong   count(void) const { return m_handler->count(); }
    inline void        setAt(const qlonglong& index, const T& value) { m_handler->setAt(index, value); }
    inline T              at(const qlonglong& index) const { return m_handler->at(index); }
    inline T           first(void) const { return m_handler->first(); }
    inline T            last(void) const { return m_handler->last();  }
    inline item       itemAt(const qlonglong& index) { return item(m_handler, index); } 
    inline item operator [] (const qlonglong& index) { return item(m_handler, index); }

public:
    inline       iterator      begin(void)       { return       iterator(m_handler, 0); }
    inline const_iterator      begin(void) const { return const_iterator(m_handler, 0); }
    inline const_iterator     cbegin(void) const { return const_iterator(m_handler, 0); }
    inline const_iterator constBegin(void) const { return const_iterator(m_handler, 0); }
    inline       iterator        end(void)       { return       iterator(m_handler, this->count()); }
    inline const_iterator        end(void) const { return const_iterator(m_handler, this->count()); }
    inline const_iterator       cend(void) const { return const_iterator(m_handler, this->count()); }
    inline const_iterator   constEnd(void) const { return const_iterator(m_handler, this->count()); }

public:
    inline qlonglong localToGlobal(const qlonglong& index);

public:
    handler       *m_handler;
    handler        m_local_handler;
    global_handler m_global_handler;

private:
    qlonglong m_count;
    qlonglong m_wid;
    qlonglong buffer_id;
    qlonglong buffer_count;

private:
    T *buffer;

private:
    dtkDistributedMapper       *m_mapper;
    dtkDistributedWorker       *m_worker;
    dtkDistributedCommunicator *m_comm;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.tpp"
