/* dtkComposerMetatype.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sat Aug  4 00:26:47 2012 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERMETATYPE_H
#define DTKCOMPOSERMETATYPE_H

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(bool*);

Q_DECLARE_METATYPE(int*);
Q_DECLARE_METATYPE(uint*);

Q_DECLARE_METATYPE(qlonglong*);
Q_DECLARE_METATYPE(qulonglong*);

Q_DECLARE_METATYPE(qreal*);
Q_DECLARE_METATYPE(double **)

Q_DECLARE_METATYPE(QString*);
Q_DECLARE_METATYPE(QStringList*);

Q_DECLARE_METATYPE(QImage*);

#endif
