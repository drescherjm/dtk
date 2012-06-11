/* dtkDistributedMessage.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: mar. oct. 11 10:46:57 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. mai 30 15:39:05 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 163
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKDISTRIBUTEDMESSAGE_H
#define DTKDISTRIBUTEDMESSAGE_H

#include "dtkDistributedExport.h"

#include <QtCore>

class dtkDistributedMessagePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedMessage
{
public:
    typedef QHash<QString, QString> dtkDistributedHeaders;

    static const qint16 CONTROLLER_RANK = -1 ;
    static const qint16 SERVER_RANK     = -2 ;
    static const qint16 CONTROLLER_RUN_RANK = -3 ;

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
             dtkDistributedMessage(Method method, QString jobid="", qint16 rank= SERVER_RANK,qint64 size=0, QString type ="json",  const QByteArray  &content = QByteArray(), const dtkDistributedHeaders& headers = dtkDistributedHeaders());
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
