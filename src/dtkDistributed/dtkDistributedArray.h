// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#pragma once

#include "dtkDistributedContainer.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedArray
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArray : public dtkDistributedContainer
{
public:
    class item;
    class iterator;

public:
      dtkDistributedArray(const qlonglong& count, dtkDistributedWorker *worker);
      dtkDistributedArray(const QVector<T>& vector, dtkDistributedWorker *worker);
     ~dtkDistributedArray(void);

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
                  handler(dtkDistributedArray<T>& array) : buffer(0), buffer_count(0) {;}
         virtual ~handler(void) {}

     public:
         virtual bool      empty(void) const { return !buffer_count; }
         virtual qlonglong count(void) const { return  buffer_count; }
         virtual void      setAt(const qlonglong& index, const T& value) { buffer[index] = value; }
         virtual T            at(const qlonglong& index) const { return buffer[index]; }
         virtual T         first(void) const { return buffer[0]; }
         virtual T          last(void) const { return buffer[buffer_count-1]; }
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
         bool      empty(void) const { return !m_count; }
         qlonglong count(void) const { return  m_count; }
         void      setAt(const qlonglong& index, const T& value);
         T    at(const qlonglong& index) const;
         T first(void) const { return this->at(0); }
         T  last(void) const { return this->at(m_count-1); }
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
         item(void) : h(0), id(0) {;}
         item(dtkDistributedArray<T>::handler *handler, const qlonglong& index) : h(handler), id(index) {;}
         item(const item& o) : h(o.h), id(o.id) {;}
        ~item(void) {;}

    public:
        item& operator = (const item& o) { h = o.h; id = o.id; return *this; }  

    public:
        T operator * (void) const { return h->at(id); }
        item& operator =  (const T& value) { h->setAt(id, value);             return *this; }
        item& operator += (const T& value) { h->setAt(id, h->at(id) + value); return *this; }
        item& operator -= (const T& value) { h->setAt(id, h->at(id) - value); return *this; }
        item& operator *= (const T& value) { h->setAt(id, h->at(id) * value); return *this; }
        item& operator /= (const T& value) { h->setAt(id, h->at(id) / value); return *this; }
        bool  operator == (const item &o) const { return id == o.id; }
        bool  operator != (const item &o) const { return id != o.id; }
        bool  operator <  (const item &o) const { return id  < o.id; }
        bool  operator >  (const item &o) const { return id  > o.id; }
        bool  operator <= (const item &o) const { return id <= o.id; }
        bool  operator >= (const item &o) const { return id >= o.id; }

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
         iterator(void) : it(item()) {;}
         iterator(dtkDistributedArray<T>::handler *handler, const qlonglong& index = 0) : it(handler, index) {;}
         iterator(const iterator& o) : it(o.it) {;}
        ~iterator(void) {;}

    public:
        iterator& operator = (const iterator& o) { it = o.it; }

    public:
        item operator *  (void)        const { return it; }
        item operator [] (qlonglong j) const { return item(it.h, it.id + j); }
        bool operator == (const iterator &o) const { return it == o.it; }
        bool operator != (const iterator &o) const { return it != o.it; }
        bool operator <  (const iterator &o) const { return it  < o.it; }
        bool operator >  (const iterator &o) const { return it  > o.it; }
        bool operator <= (const iterator &o) const { return it <= o.it; }
        bool operator >= (const iterator &o) const { return it >= o.it; }
        iterator& operator ++ (void) { ++it; return *this; }
        iterator  operator ++ (int)  { ++it; return iterator(it.h, it.id-1); }
        iterator& operator -- (void) { --it; return *this; }
        iterator  operator -- (int)  { --it; return iterator(it.h, it.id+1); }
        iterator& operator += (qlonglong j) { it.id += j; return *this; }
        iterator& operator -= (qlonglong j) { it.id -= j; return *this; }
        iterator  operator +  (qlonglong j) const { return iterator(it.h, it.id + j); }
        iterator  operator -  (qlonglong j) const { return iterator(it.h, it.id - j); }
        qlonglong operator -  (const iterator& o) const { return it.id - o.it.id; }
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
                  const_iterator(void) : h(0), id(0) {;}
                  const_iterator(const dtkDistributedArray<T>::handler *handler, const qlonglong& index = 0) : h(handler), id(index) {;}
                  const_iterator(const const_iterator& o) : h(o.h), id(o.id) {;}
        explicit  const_iterator(const iterator& o) : h(o.h), id(o.id) {;}
                 ~const_iterator(void) {;}

    public:
        const_iterator& operator = (const const_iterator& o) { h = o.h; id = o.id; }

    public:
        T operator *  (void)        const { return h->at(id); }
        T operator [] (qlonglong j) const { return h->at(id + j); }
        bool operator == (const const_iterator &o) const { return id == o.id; }
        bool operator != (const const_iterator &o) const { return id != o.id; }
        bool operator <  (const const_iterator &o) const { return id  < o.id; }
        bool operator >  (const const_iterator &o) const { return id  > o.id; }
        bool operator <= (const const_iterator &o) const { return id <= o.id; }
        bool operator >= (const const_iterator &o) const { return id >= o.id; }
        const_iterator& operator ++ (void) { ++id; return *this; }
        const_iterator  operator ++ (int)  { ++id; return const_iterator(h, id-1); }
        const_iterator& operator -- (void) { --id; return *this; }
        const_iterator  operator -- (int)  { --id; return const_iterator(h, id+1); }
        const_iterator& operator += (qlonglong j) { id += j; return *this; }
        const_iterator& operator -= (qlonglong j) { id -= j; return *this; }
        const_iterator  operator +  (qlonglong j) const { return const_iterator(h, id + j); }
        const_iterator  operator -  (qlonglong j) const { return const_iterator(h, id - j); }
        qlonglong       operator -  (const const_iterator& o) const { return id - o.id; }
    };
    friend class const_iterator;

private:
    void initialize(void);

public:
    void setMode(const dtkDistributed::Mode& mode);
    
public:
    bool        empty(void) const { return m_handler->empty(); }
    qlonglong   count(void) const { return m_handler->count(); }
    void        setAt(const qlonglong& index, const T& value) { m_handler->setAt(index, value); }
    T              at(const qlonglong& index) const { return m_handler->at(index); }
    T           first(void) const { return m_handler->first(); }
    T            last(void) const { return m_handler->last();  }
    item       itemAt(const qlonglong& index) { return item(m_handler, index); } 
    item operator [] (const qlonglong& index) { return item(m_handler, index); }

public:
          iterator      begin(void)       { return       iterator(m_handler, 0); }
    const_iterator      begin(void) const { return const_iterator(m_handler, 0); }
    const_iterator     cbegin(void) const { return const_iterator(m_handler, 0); }
    const_iterator constBegin(void) const { return const_iterator(m_handler, 0); }
          iterator        end(void)       { return       iterator(m_handler, this->count()); }
    const_iterator        end(void) const { return const_iterator(m_handler, this->count()); }
    const_iterator       cend(void) const { return const_iterator(m_handler, this->count()); }
    const_iterator   constEnd(void) const { return const_iterator(m_handler, this->count()); }

public:
    qlonglong localToGlobal(const qlonglong& index);

public:
    void setAtGlobal(const qlonglong& index, const T& value) { m_global_handler.setAt(index, value); }
    T       atGlobal(const qlonglong& index) const { return m_global_handler.at(index); }

public:
    handler       *m_handler;
    handler        m_local_handler;
    global_handler m_global_handler;

private:
    qlonglong m_count;
    qlonglong buffer_id;
    qlonglong buffer_count;

private:
    T *buffer;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.tpp"

// 
// dtkDistributedArray.h ends here
