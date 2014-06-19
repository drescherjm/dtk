/* dtkDistributedMapper.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Thu Feb  7 10:55:57 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedMapper.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkDistributedMapperPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkDistributedMapperPrivate
{
public:
     dtkDistributedMapperPrivate(void) {;}
    ~dtkDistributedMapperPrivate(void) {;}

public:
    void setMapping(const qlonglong& id_number, const qlonglong& pu_number);
    void initMap(const qlonglong& map_size, const qlonglong& pu_size);
    void setMap(const qlonglong& local_map_size, const qlonglong& pu_id);

public:
    qlonglong localToGlobal(const qlonglong&  local_id, const qlonglong& pu_id) const;

    qlonglong globalToLocal(const qlonglong& global_id) const;

    qlonglong count(const qlonglong& pu_id) const;

    qlonglong owner(const qlonglong& global_id) const;

    QVector<qlonglong> readers(const qlonglong& global_id) const;

public:
    qlonglong id_count;
    qlonglong pu_count;
    qlonglong step;

    QVector<qlonglong> map;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedMapperPrivate implementation
// /////////////////////////////////////////////////////////////////

void dtkDistributedMapperPrivate::setMapping(const qlonglong& id_number, const qlonglong& pu_number)
{
    this->id_count = id_number;
    this->pu_count = pu_number;

    this->map.reserve(this->pu_count);

    if (this->pu_count == 1) {
        this->map << 0;
        this->step = this->id_count;

    } else if (this->id_count < this->pu_count  ) {

        qDebug() << "NOT YET IMPLEMENTED";
        qApp->quit();

    } else if (this->id_count < this->pu_count * 2) {

        for (qlonglong i = 0; i < this->id_count - this->pu_count; ++i)
            this->map << i * 2;

        qlonglong start = (this->id_count - this->pu_count) *2;

        for (qlonglong i = this->id_count - this->pu_count; i < this->pu_count; ++i)
            this->map << start++;

        this->step = 0;
    } else {

        this->step = qRound(this->id_count / (1. * this->pu_count));
        for (qlonglong i = 0; i < this->pu_count - 1; ++i) {
            this->map << i * this->step;
        }

        this->map << (this->map.at(this->pu_count - 2) + this->step);
    }
}

void dtkDistributedMapperPrivate::initMap(const qlonglong& map_size, const qlonglong& pu_size)
{
    this->id_count = map_size;
    this->pu_count = pu_size;
    
    this->map.resize(this->pu_count);
    this->step = 0;
}

void dtkDistributedMapperPrivate::setMap(const qlonglong& offset, const qlonglong& pu_id)
{
    this->map[pu_id] = offset;
}

qlonglong dtkDistributedMapperPrivate::localToGlobal(const qlonglong& local_id, const qlonglong& pu_id) const
{
    return ( local_id + this->map.at(pu_id) );
}

qlonglong dtkDistributedMapperPrivate::globalToLocal(const qlonglong& global_id) const
{
    qlonglong pu_id = this->owner(global_id);

    return ( global_id - this->map.at(pu_id) );
}

qlonglong dtkDistributedMapperPrivate::count(const qlonglong& pu_id) const
{
    if ( pu_id != (this->pu_count - 1) )
        return ( this->map.at(pu_id + 1) - this->map.at(pu_id) );

    else
        return ( this->id_count - this->map.at(pu_id) );
}

qlonglong dtkDistributedMapperPrivate::owner(const qlonglong& global_id) const
{
    if (this->step > 0) {
        return qMin((qlonglong)(global_id / this->step), this->pu_count-1);
    } else {
        qlonglong current_id = this->map.last();
        qlonglong pid = this->pu_count-1;
        while (global_id < current_id) {
            current_id = this->map.at(--pid);
        }
        return pid;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkDistributedMapper implementation
// /////////////////////////////////////////////////////////////////

dtkDistributedMapper::dtkDistributedMapper(void) : QObject(), d(new dtkDistributedMapperPrivate)
{

}

dtkDistributedMapper::~dtkDistributedMapper(void)
{
    delete d;
}

void dtkDistributedMapper::setMapping(const qlonglong& id_count, const qlonglong& pu_count)
{
    d->setMapping(id_count, pu_count);
}

void dtkDistributedMapper::initMap(const qlonglong& map_size, const qlonglong& pu_size)
{
    d->initMap(map_size, pu_size);
}

void dtkDistributedMapper::setMap(const qlonglong& offset, const qlonglong& pu_id)
{
    d->setMap(offset, pu_id);
}

qlonglong dtkDistributedMapper::localToGlobal(const qlonglong& local_id, const qlonglong& pu_id) const
{
    return d->localToGlobal(local_id, pu_id);
}

qlonglong dtkDistributedMapper::globalToLocal(const qlonglong& global_id) const
{
    return d->globalToLocal(global_id);
}

qlonglong dtkDistributedMapper::count(const qlonglong& pu_id) const
{
    return d->count(pu_id);
}

qlonglong dtkDistributedMapper::startIndex(const qlonglong& pu_id) const
{
    return d->map[pu_id];
}

qlonglong dtkDistributedMapper::owner(const qlonglong& global_id) const
{
    return d->owner(global_id);
}

