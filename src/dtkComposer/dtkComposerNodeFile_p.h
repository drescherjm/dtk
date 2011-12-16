/* dtkComposerNodeFile_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Oct 13 01:14:28 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 13 01:22:19 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEFILE_P_H
#define DTKCOMPOSERNODEFILE_P_H

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

class dtkComposerNodeProperty;

class dtkComposerNodeFilePrivate : public QObject
{
    Q_OBJECT

public:
    dtkComposerNodeProperty *property_output_file_name;
    dtkComposerNodeProperty *property_output_file_text;
    dtkComposerNodeProperty *property_output_file_url;

public slots:
    void onRequestFinished(int id, bool error);

public:
    QString file;
    QUrl url;

    int dwnl_id;
    int dwnl_ok;
};

#endif
