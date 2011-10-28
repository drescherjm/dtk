/* dtkDistributedMessage.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: mar. oct. 11 10:46:57 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 13 17:12:24 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 139
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKDISTRIBUTEDMESSAGE_H
#define DTKDISTRIBUTEDMESSAGE_H

#include <QtCore>
#include "dtkDistributedExport.h"

class dtkDistributedMessagePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedMessage
{

public:
    typedef QHash<QString, QString> dtkDistributedHeaders;

    enum Method {
        STATUS  ,
        OKSTATUS,
        NEWJOB  ,
        OKJOB   ,
        DELJOB  ,
        OKDEL   ,
        ERRORDEL,
        STARTJOB,
        ENDJOB  ,
        DATA    ,
        SETRANK
    };

             dtkDistributedMessage(void);
             dtkDistributedMessage(Method method, QString jobid="", qint16 rank=-2,qint64 size=0, QString type ="json", const QByteArray  &content = QByteArray(), const dtkDistributedHeaders& headers = dtkDistributedHeaders());
    virtual ~dtkDistributedMessage(void);


    void addHeader(QString name, QString value);
    void setHeader(const QString &line);
    void setMethod(QString method);
    void setMethod(Method method);
    void setJobid(const QString &jobid);
    void setRank(qint16 rank);
    void setType(const QString &header);
    void setSize(const QString &header);
    void setContent(QByteArray &content);

    Method method(void);
    QString req(void);
    QString jobid(void);
    qint16  rank(void);
    dtkDistributedHeaders headers();
    QString header(const QString &name);
    QString type(void);
    qint64 size(void);
    QByteArray &content(void);

private:
    dtkDistributedMessagePrivate *d;
};

#endif
