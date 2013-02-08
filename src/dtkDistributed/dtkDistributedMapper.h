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
    void setMapping(const qlonglong& id_count, const qlonglong& pu_count);

public:
    qlonglong localToGlobal(const qlonglong& local_id, const qlonglong& pu_id) const;

    qlonglong globalToLocal(const qlonglong& global_id) const;

    qlonglong count(const qlonglong& pu_id) const;

    qlonglong owner(const qlonglong& global_id) const;

private:
    dtkDistributedMapperPrivate *d;
};
