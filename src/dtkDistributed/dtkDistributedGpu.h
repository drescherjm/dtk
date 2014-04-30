/* dtkDistributedGpu.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:32:38 2010 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtCore>

class dtkDistributedNode;
class dtkDistributedGpuPrivate;

class dtkDistributedGpu : public QObject
{
    Q_OBJECT

public:
     dtkDistributedGpu(dtkDistributedNode *parent);
    ~dtkDistributedGpu(void);

public:
    enum Architecture {
           Nvidia_10 = 0x1,
           Nvidia_13 = 0x2,
           Nvidia_20 = 0x4,
              AMD = 0x8
    };

    Architecture architecture(void);

    void setArchitecture(Architecture arch);

    enum Model {
           T10    = 0x1,
           C2050  = 0x2,
           C2070  = 0x4
    };

    Model model(void);

    void setModel(Model model);


private:
    dtkDistributedGpuPrivate *d;
};

