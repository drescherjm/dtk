/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb  9 11:15:14 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 10 16:40:47 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 311
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstMainWindow.h"

#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkAbstractView.h>

#include <QtOpenGL>

// /////////////////////////////////////////////////////////////////
// tstMainWindow
// /////////////////////////////////////////////////////////////////

class tstMainWindowPrivate
{
public:
    QLineEdit *host;
    QLineEdit *port;
    QLabel *status;

    QPushButton *connectButton;
    QPushButton *disconnectButton;

public:
    QTcpSocket *socket;

    quint16 size;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent), d(new tstMainWindowPrivate)
{
    // /////////////////////////////////////////////////////////////////
    // Network
    // /////////////////////////////////////////////////////////////////

    d->socket = NULL;
    d->size = 0;

    // /////////////////////////////////////////////////////////////////
    // Ui
    // /////////////////////////////////////////////////////////////////

    QWidget *central = new QWidget(this);

    d->host = new QLineEdit("", central);
    d->port = new QLineEdit("", central);
    d->status = new QLabel("", central);
    d->status = new QLabel("<font color=\"red\">Not connected</font>", central);
    d->status->setTextFormat(Qt::RichText);

    d->connectButton = new QPushButton("Connect", this);
    d->disconnectButton = new QPushButton("Disconnect", this);

    QWidget *buttons = new QWidget(central);

    QHBoxLayout *buttonsLayout = new QHBoxLayout(buttons);
    buttonsLayout->addWidget(d->connectButton);
    buttonsLayout->addWidget(d->disconnectButton);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Host:", d->host);
    formLayout->addRow("Port:", d->port);
    formLayout->addRow("Status:", d->status);
    formLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addLayout(formLayout);
    layout->addWidget(buttons);

    this->setCentralWidget(central);
    this->setWindowTitle("dtkVrDeviceClient");

    connect(d->connectButton, SIGNAL(clicked()), this, SLOT(onConnect()));
    connect(d->disconnectButton, SIGNAL(clicked()), this, SLOT(onDisconnect()));

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onDisconnect()));
}

tstMainWindow::~tstMainWindow(void)
{
    delete d;

    d = NULL;
}

void tstMainWindow::onConnect(void)
{
    if (d->host->text().isNull() && d->port->text().isNull())
        return;

    if(!d->socket)
        d->socket = new QTcpSocket(this);

    connect(d->socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(d->socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(d->socket, SIGNAL(readyRead()), this, SLOT(onRead()));
    connect(d->socket, SIGNAL(  error(QAbstractSocket::SocketError)), 
                 this,   SLOT(onError(QAbstractSocket::SocketError)));

    d->socket->connectToHost(d->host->text(), d->port->text().toInt());

    if (d->socket->state() == QAbstractSocket::ConnectingState)
        d->status->setText("<font color=\"yellow\">Connecting</font>");
}

void tstMainWindow::onConnected(void)
{
    if (d->socket->state() == QAbstractSocket::ConnectedState)
        d->status->setText("<font color=\"green\">Connected</font>");
}

void tstMainWindow::onDisconnect(void)
{
    if (d->socket)
        d->socket->abort();

    d->size = 0;

    d->status->setText("<font color=\"red\">Disconnected</font>");
}

void tstMainWindow::onDisconnected(void)
{
    if (d->socket && d->socket->state() == QAbstractSocket::UnconnectedState)
        d->status->setText("<font color=\"red\">Disconnected</font>");
}

void tstMainWindow::onRead(void)
{
    QDataStream in(d->socket);
    in.setVersion(QDataStream::Qt_4_6);

    if(d->size == 0)
        if(d->socket->bytesAvailable() < (int)(sizeof(quint16)))
            return;
        else
            in >> d->size;

    if(d->socket->bytesAvailable() < d->size)
        return;

    float tx; in >> tx;
    float ty; in >> ty;
    float tz; in >> tz;
    float rx; in >> rx;
    float ry; in >> ry;
    float rz; in >> rz;
    
    qDebug() << "client:" << tx << ty << tz << rx << ry << rz;

    d->size = 0;
}

void tstMainWindow::onError(QAbstractSocket::SocketError error)
{
    switch (error) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "dtkVrDeviceClient", "The host was not found. Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "dtkVrDeviceClient", "The connection was refused by the peer. Make sure the server is running, and check that the host name and port settings are correct.");
        break;
    default:
        QMessageBox::information(this, "dtkVrDeviceClient", QString("The following error occurred: %1.").arg(d->socket->errorString()));
        break;
    }
}
