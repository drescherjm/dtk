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
Q_DECLARE_METATYPE(QProcessEnvironment);

class dtkComposerNodeExecPrivate
{
public:
    QString command;
    QProcessEnvironment processEnv;
    qlonglong timeout;

public:
    dtkComposerTransmitterReceiver<QString>             receiver_command;
    dtkComposerTransmitterReceiverVariant                  receiver_args;
    dtkComposerTransmitterReceiver<qlonglong>           receiver_timeout;
    dtkComposerTransmitterReceiver<QProcessEnvironment>     receiver_env;

public:
    dtkComposerTransmitterEmitter<QString>                emitter_stdout;
    dtkComposerTransmitterEmitter<QString>                emitter_stderr;
    dtkComposerTransmitterEmitter<qlonglong>           emitter_exit_code;
};


dtkComposerNodeExec::dtkComposerNodeExec(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeExecPrivate)
{
    // QList<int> variant_list;
    // variant_list << QMetaType::QString << QMetaType::QStringList;
    // d->receiver_args.setDataTypes(variant_list);

    this->appendReceiver(&(d->receiver_command));
    this->appendReceiver(&(d->receiver_args));
    this->appendReceiver(&(d->receiver_timeout));
    this->appendReceiver(&(d->receiver_env));

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

        QFileInfo file(d->command);
        bool exists = false;

        if (file.isRelative()) {

            QStringList PATH =  QProcessEnvironment::systemEnvironment().value("PATH").split(":") ;
            QDir::setSearchPaths("bin", PATH);
            exists = QFile("bin:" + d->command).exists();
            dtkTrace() << d->command << " is relative, check if exists:" << exists;
        } else {
            exists = file.exists();
            dtkTrace() << d->command << " is absolute, check if exists:" << exists;
        }

        if (!exists) {
            dtkWarn() << "Command not found in PATH " << d->command;
            d->emitter_exit_code.setData(127);
            d->emitter_stdout.clearData();
            d->emitter_stderr.clearData();
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

        if (!d->receiver_env.isEmpty()) {
            d->processEnv = d->receiver_env.data();
        }

        QProcess cmd;
        cmd.setProcessEnvironment(d->processEnv);
        cmd.start(d->command, arglist);
        QString stdout_data;
        QString stderr_data;

        if (cmd.waitForFinished(d->timeout)) {
            if (d->emitter_stdout.receiverCount()) {
                QByteArray a = cmd.readAllStandardOutput();
                stdout_data = QString::fromLocal8Bit(a.data());
            } else {
                dtkInfo() << "no output from command " << d->command;
            }

            if (d->emitter_stderr.receiverCount()) {
                QByteArray a = cmd.readAllStandardError();
                stderr_data = QString::fromLocal8Bit(a.data());
            }
        } else {
            dtkWarn() << "Timeout while running command " << d->command;
        }

        int exit_code = cmd.exitCode();
        d->emitter_exit_code.setData(exit_code);
        d->emitter_stdout.setData(stdout_data);
        d->emitter_stderr.setData(stderr_data);

    } else {
        dtkWarn() << Q_FUNC_INFO << "The input command path is not set. Nothing is done.";
    }
}

