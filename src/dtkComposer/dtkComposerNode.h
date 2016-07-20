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

#include "dtkComposerExport.h"

#include <QtCore>

class dtkComposerNodePrivate;
class dtkComposerTransmitter;
class dtkComposerNodeMetaData;
class dtkComposerViewWidget;

// ///////////////////////////////////////////////////////////////////
// dtkComposerNode declaration
// ///////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNode
{
public:
    dtkComposerNode(void);
    virtual ~dtkComposerNode(void);

public:
    enum Kind {
        Unknown = 0,
        Atomic = 1,
        Composite = 2,
        Control = 3,
        Proxy = 4,
        Data = 5,
        Process = 6,
        View = 7,
        Actor = 8
    };

public:
    void setNodeMetaData(dtkComposerNodeMetaData *meta_data);
    dtkComposerNodeMetaData *nodeMetaData(void) const;

public:
    void appendEmitter(dtkComposerTransmitter *emitter);
    void removeEmitter(dtkComposerTransmitter *emitter);

    dtkComposerTransmitter *removeEmitter(int index);

    void appendReceiver(dtkComposerTransmitter *receiver);
    void removeReceiver(dtkComposerTransmitter *receiver);

    dtkComposerTransmitter *removeReceiver(int index);

    QList<dtkComposerTransmitter *> emitters(void);
    QList<dtkComposerTransmitter *> receivers(void);

public:
    virtual QString type(void);

public:
    virtual QString titleHint(void);

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

public:
    virtual dtkComposerViewWidget *widget(void);
    virtual QWidget *editor(void);

public:
    QT_DEPRECATED void setTitleHint(const QString& hint);

public:
    QT_DEPRECATED void  setInputLabelHint(const QString& hint, int port);
    QT_DEPRECATED void setOutputLabelHint(const QString& hint, int port);

private:
    dtkComposerNodePrivate *d;
};

//
// dtkComposerNode.h ends here
