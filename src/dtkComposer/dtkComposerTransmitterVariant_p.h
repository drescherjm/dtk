/* dtkComposerTransmitterVariant_p.h --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Fri Aug  3 14:36:46 2012 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_P_H
#define DTKCOMPOSERTRANSMITTERVARIANT_P_H

#include <dtkConfig.h>

#if defined(DTK_BUILD_PLOT) && defined(DTK_HAVE_PLOT)
#include <dtkPlot/dtkPlotCurve.h>
#endif

#include <QtCore>

class dtkComposerTransmitter;
class dtkComposerTransmitterVariant;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterVariantPrivate
{
public:
    enum Type {
        RealStar = 0,
        LongLongStar = 1,
        StringStar = 2,
        BoolStar = 3
    };

public:
  static const qlonglong dtkVector3DReal_Id     = 512;
  static const qlonglong dtkVectorReal_Id       = 513;
  static const qlonglong dtkQuaternionReal_Id   = 514;
  static const qlonglong dtkMatrixReal_Id       = 515;
  static const qlonglong dtkMatrixSquareReal_Id = 516;
  static const qlonglong dtkAbstractData_Id     = 517;
  static const qlonglong dtkPlotCurve_Id        = 518;
  static const qlonglong dtkVectorInteger_Id    = 519;
  static const qlonglong dtkAbstractContainer_Id= 520;

public:
    dtkComposerTransmitterVariantPrivate(void) {
        metatypes[0] = qMetaTypeId<qreal*>(0);
        metatypes[1] = qMetaTypeId<qlonglong*>(0);
        metatypes[2] = qMetaTypeId<QString*>(0);
        metatypes[3] = qMetaTypeId<bool*>(0);
    }

public:
    QList<dtkComposerTransmitter *> emitters;
    QList<dtkComposerTransmitterVariant *> variants;

public:
    dtkComposerTransmitter        *active_emitter;
    dtkComposerTransmitterVariant *active_variant;

public:
    QList<int> data_types;

public:
    dtkComposerTransmitterVariant *twin;

    bool twinned;

    bool already_ask;

public:
    bool      *value_b;
    qlonglong *value_i;
    qreal     *value_r;
    QString   *value_s;

public:
    int metatypes[4];

public:
    QVariant m_variant;

public:
    bool data_owner;

#if defined(DTK_BUILD_PLOT) && defined(DTK_HAVE_PLOT)
public:
    dtkPlotCurve curve;
#endif

};

#endif
