/* @(#)dtkComposerNodeExec.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/05/19 08:26:02
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerNodeExec.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include <dtkLog/dtkLogger.h>

#include <QtCore>

class dtkComposerNodeExecPrivate
{
public:
    QString command;
    QString stdout_data;
    QString stderr_data;
    qlonglong timeout;
    qlonglong exit_code;

public:
    dtkComposerTransmitterReceiver<QString>   receiver_command;
    dtkComposerTransmitterReceiverVariant        receiver_args;
    dtkComposerTransmitterReceiver<qlonglong> receiver_timeout;

public:
    dtkComposerTransmitterEmitter<QString>      emitter_stdout;
    dtkComposerTransmitterEmitter<QString>      emitter_stderr;
    dtkComposerTransmitterEmitter<qlonglong> emitter_exit_code;
};


dtkComposerNodeExec::dtkComposerNodeExec(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeExecPrivate)
{
    // QList<int> variant_list;
    // variant_list << QMetaType::QString << QMetaType::QStringList;
    // d->receiver_args.setDataTypes(variant_list);

    this->appendReceiver(&(d->receiver_command));
    this->appendReceiver(&(d->receiver_args));
    this->appendReceiver(&(d->receiver_timeout));

    // wait forever by default
    d->timeout = -1;

    this->appendEmitter(&(d->emitter_stdout));
    this->appendEmitter(&(d->emitter_stderr));
    this->appendEmitter(&(d->emitter_exit_code));

}

dtkComposerNodeExec::~dtkComposerNodeExec(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeExec::run(void)
{
    if (!d->receiver_command.isEmpty() ) {
        d->command = d->receiver_command.data();
        QFile file(d->command);
        if (!file.exists()) {
            dtkWarn() << "Command does not exists! "<< d->command;
            return;
        }

        QStringList arglist;
        if (!d->receiver_args.isEmpty() ) {
            int data_type = d->receiver_args.data().type();

            if (data_type == QMetaType::QStringList) {
                arglist = d->receiver_args.data<QStringList>();

            } else {
                QString args = d->receiver_args.data<QString>();
                if (args.count() > 0)
                    arglist = args.split(" ");
            }
        }
        if (!d->receiver_timeout.isEmpty() ) {
            d->timeout = d->receiver_timeout.data();
        }
        QProcess cmd;

        cmd.start(d->command, arglist);

        if (cmd.waitForFinished(d->timeout)) {
            if (d->emitter_stdout.receiverCount()) {
                QByteArray a = cmd.readAllStandardOutput();
                d->stdout_data = QString::fromLocal8Bit(a.data());
            } else {
                dtkInfo() << "no output from command " << d->command;
            }
            if (d->emitter_stderr.receiverCount()) {
                QByteArray a = cmd.readAllStandardError();
                d->stderr_data = QString::fromLocal8Bit(a.data());
            }
        } else {
            dtkWarn() << "Timeout while running command " << d->command;
        }
        d->exit_code = cmd.exitCode();
        d->emitter_exit_code.setData(d->exit_code);
        d->emitter_stdout.setData(d->stdout_data);
        d->emitter_stderr.setData(d->stderr_data);

    } else {
         dtkWarn() << Q_FUNC_INFO << "The input command path is not set. Nothing is done.";
    }

}

