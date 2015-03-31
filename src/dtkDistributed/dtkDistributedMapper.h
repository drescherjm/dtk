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

#include "dtkDistributedExport.h"

#include <QtCore/QObject>

template <typename T> class QVector;

class dtkDistributedMapperPrivate;

// /////////////////////////////////////////////////////////////////
// dtkDistributedMapper interface
// /////////////////////////////////////////////////////////////////

class DTKDISTRIBUTED_EXPORT dtkDistributedMapper : public QObject
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
    qlonglong globalToLocal(const qlonglong& global_id, const qlonglong& owner) const;

    qlonglong count(void) const;
    qlonglong count(const qlonglong& pu_id) const;
    qlonglong countMax(void) const;

    qlonglong firstIndex(const qlonglong& pu_id) const;
    qlonglong  lastIndex(const qlonglong& pu_id) const;

    qlonglong owner(const qlonglong& global_id);

private:
    dtkDistributedMapperPrivate *d;
};

//
// dtkDistributedMapper.h ends here
