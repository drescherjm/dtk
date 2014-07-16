/* dtkDistributedMapper.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Thu Feb  7 10:40:37 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <QtCore/QObject>

template <typename T> class QVector;
class dtkDistributedMapperPrivate;

// /////////////////////////////////////////////////////////////////
// dtkDistributedMapper interface
// /////////////////////////////////////////////////////////////////

class dtkDistributedMapper : public QObject
{
    Q_OBJECT

public:
     dtkDistributedMapper(void);
    ~dtkDistributedMapper(void);

public:
    bool deref(void);
    bool   ref(void);

public:
    void setMapping(const qlonglong& id_count, const qlonglong& pu_count);

    void initMap(const qlonglong& map_size, const qlonglong& pu_size);
    void setMap(const qlonglong& offset, const qlonglong& pu_id);

public:
    qlonglong localToGlobal(const qlonglong& local_id, const qlonglong& pu_id) const;

    qlonglong globalToLocal(const qlonglong& global_id) const;

    qlonglong count(const qlonglong& pu_id) const;
    qlonglong startIndex(const qlonglong& pu_id) const;
    qlonglong  lastIndex(const qlonglong& pu_id) const;

    qlonglong owner(const qlonglong& global_id, qlonglong pu_id = -1) const;

private:
    dtkDistributedMapperPrivate *d;
};
