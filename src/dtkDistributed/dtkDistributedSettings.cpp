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

#include "dtkDistributedSettings.h"
#include <dtkLog>

// helper function
QString extract_key(QUrl server)
{
#if defined(Q_OS_MAC)
    return server.host().replace(".", "_");
#else
    return server.host();
#endif
}
//

dtkDistributedSettings::dtkDistributedSettings(void) : QSettings(QSettings::IniFormat, QSettings::UserScope, "inria", "dtk-distributed")
{
    this->beginGroup("communicator");

    if (!this->allKeys().contains("plugins")) {
        this->setValue("plugins", QString());
    }

    this->sync();
    this->endGroup();
}

dtkDistributedSettings::~dtkDistributedSettings(void)
{

}

QString dtkDistributedSettings::path(const QUrl server)
{
    this->beginGroup("server");

    QString key = extract_key(server);
    QString defaultPath =  "./dtkDistributedServer";

    if (!this->contains(key + "_server_path")) {
        dtkInfo() << "Filling in empty path in settings with default path:" << defaultPath;
    }

    QString path = this->value(key + "_server_path", defaultPath).toString();
    dtkDebug() << "Found server path in settings:" << path;
    this->endGroup();
    return path;
}

QString dtkDistributedSettings::server_type(const QUrl server)
{
    this->beginGroup("server");

    QString key = extract_key(server);
    QString defaultType =  "local";

    if (!this->contains(key + "_server_type")) {
        dtkInfo() << "Filling in empty type in settings with default type:" << defaultType;
    }

    QString type = this->value(key + "_server_type", defaultType).toString();
    dtkDebug() << "Found server path in settings:" << type;
    this->endGroup();
    return type;
}

bool dtkDistributedSettings::use_ssh_tunnel(const QUrl server)
{
    this->beginGroup("server");
    QString key = extract_key(server);
    QString forward = key + "_server_use_tunnel";
    bool use_tunnel = false;

    if (this->contains(forward) && this->value(forward).toString() == "true") {
        use_tunnel = true;
        dtkDebug() << "ssh port forwarding is set for server " << server.host();
    }

    this->endGroup();
    return use_tunnel;
}


//
// dtkDistributedSettings.cpp ends here
