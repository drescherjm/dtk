/* dtkDistributedMessage.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: mar. oct. 11 10:46:57 2011 (+0200)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKDISTRIBUTEDMESSAGE_H
#define DTKDISTRIBUTEDMESSAGE_H

#include "dtkDistributedSupportExport.h"

#include <QtCore>

class dtkDistributedMessagePrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedMessage
{
public:
    typedef QHash<QString, QString> dtkDistributedHeaders;

    static const qint16 CONTROLLER_RANK = -1 ;
    static const qint16 SERVER_RANK     = -2 ;
    static const qint16 CONTROLLER_RUN_RANK = -5 ;
    static const qint16 SLAVE_RANK = -4 ; // identify the slave tcp connection that handle composition send/receive.

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
        SETRANK ,
        STOP
    };

             dtkDistributedMessage(void);
             dtkDistributedMessage(Method method, QString jobid="", int rank= SERVER_RANK,qint64 size=0, QString type ="json",  const QByteArray  &content = QByteArray(), const dtkDistributedHeaders& headers = dtkDistributedHeaders());
    virtual ~dtkDistributedMessage(void);

public:
    void addHeader(QString name, QString value);
    void setHeader(const QString &line);
    void setMethod(QString method);
    void setMethod(Method method);
    void setJobid(const QString &jobid);
    void setRank(qint16 rank);
    void setType(const QString &header);
    void setSize(const QString &header);
    void setContent(QByteArray &content);

public:
    Method method(void);
    QString         req(void);
    QString       jobid(void);
    int            rank(void);
    QString      header(const QString &name);
    QString        type(void);
    qint64         size(void);
    QByteArray &content(void);

public:
    dtkDistributedHeaders headers();

private:
    dtkDistributedMessagePrivate *d;
};

#endif
