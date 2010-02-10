/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb  9 11:15:14 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb  9 23:10:07 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 154
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstMainWindow.h"

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

#include <dtkVr/dtkDeviceTdx.h>

// /////////////////////////////////////////////////////////////////
// tstMainWindowPrivate
// /////////////////////////////////////////////////////////////////

class tstMainWindowPrivate
{
public:
    static void tdxHandler(float tx, float ty, float tz, float rx, float ry, float rz);

    static tstMainWindowPrivate *self;

public: // GUI PART -------------------------
    QLabel *host;
    QLabel *port;
    QLabel *status;

    QPushButton *startButton;
    QPushButton *stopButton;

    QTextEdit *clients;

public: // NETWORK PART ---------------------
    QTcpServer *server;

    QList<QTcpSocket *> sockets;

public: // DEVICE PART ----------------------
    dtkDeviceTdx *tdx;
};

void tstMainWindowPrivate::tdxHandler(float tx, float ty, float tz, float rx, float ry, float rz)
{
    qDebug() << "server:" << tx << ty << tz << rx << ry << rz;

    QByteArray block;
    
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out << (quint16)0;
    out << tx << ty << tz << rx << ry << rz;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    foreach(QTcpSocket *socket, self->sockets)
        socket->write(block);
}

tstMainWindowPrivate *tstMainWindowPrivate::self = NULL;

// /////////////////////////////////////////////////////////////////
// tstMainWindow
// /////////////////////////////////////////////////////////////////

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent), d(new tstMainWindowPrivate)
{
    d->self = d;

    // /////////////////////////////////////////////////////////////////
    // Vr
    // /////////////////////////////////////////////////////////////////

    d->tdx = NULL;

    // /////////////////////////////////////////////////////////////////
    // Network
    // /////////////////////////////////////////////////////////////////

    d->server = NULL;

    // /////////////////////////////////////////////////////////////////
    // User interface
    // /////////////////////////////////////////////////////////////////

    QWidget *central = new QWidget(this);

    d->host = new QLabel("", central);
    d->port = new QLabel("", central);
    d->status = new QLabel("<font color=\"red\">Not running</font>", central);
    d->status->setTextFormat(Qt::RichText);

    d->startButton = new QPushButton("Start", this);
    d->stopButton = new QPushButton("Stop", this);

    d->clients = new QTextEdit(this);
    d->clients->setReadOnly(true);

    QWidget *buttons = new QWidget(central);

    QHBoxLayout *buttonsLayout = new QHBoxLayout(buttons);
    buttonsLayout->addWidget(d->startButton);
    buttonsLayout->addWidget(d->stopButton);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Host:", d->host);
    formLayout->addRow("Port:", d->port);
    formLayout->addRow("Status:", d->status);
    formLayout->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addLayout(formLayout);
    layout->addWidget(d->clients);
    layout->addWidget(buttons);
    
    this->setCentralWidget(central);
    this->setWindowTitle("dtkVrDeviceServer");

    connect(d->startButton, SIGNAL(clicked()), this, SLOT(onStart()));
    connect(d->stopButton, SIGNAL(clicked()), this, SLOT(onStop()));

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onStop()));
}

tstMainWindow::~tstMainWindow(void)
{
    delete d;

    d = NULL;
}

void tstMainWindow::onStart(void)
{
    // /////////////////////////////////////////////////////////////////
    // Vr
    // /////////////////////////////////////////////////////////////////

    if(!d->tdx)
        d->tdx = new dtkDeviceTdx;

    d->tdx->startConnection();
    d->tdx->registerHandler(tstMainWindowPrivate::tdxHandler);

    // /////////////////////////////////////////////////////////////////
    // Network
    // /////////////////////////////////////////////////////////////////

    if(!d->server)
        d->server = new QTcpServer(this);

    if(!d->server->listen()) {
        QMessageBox::critical(this, "dtkVrDeviceServer", QString("Unable to start the server: %1").arg(d->server->errorString()));
        d->status->setText("<font color=\"red\">not running</font>");
        return;
    }

    connect(d->server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    // /////////////////////////////////////////////////////////////////
    // Ui
    // /////////////////////////////////////////////////////////////////

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    // QString ipAddress = QHostInfo::fromName(QHostInfo::localHostName()).addresses().first().toString();
    
    d->host->setText(ipAddress);
    d->port->setText(QString::number(d->server->serverPort()));
    d->status->setText("<font color=\"green\">Running</font>");
}

void tstMainWindow::onStop(void)
{
    // /////////////////////////////////////////////////////////////////
    // Network
    // /////////////////////////////////////////////////////////////////

    if (d->server && d->server->isListening())
        d->server->close();

    // /////////////////////////////////////////////////////////////////
    // Ui
    // /////////////////////////////////////////////////////////////////

    d->host->setText("");
    d->port->setText("");
    d->clients->clear();
    d->status->setText("<font color=\"red\">Not running</font>");

    // /////////////////////////////////////////////////////////////////
    // Vr
    // /////////////////////////////////////////////////////////////////

    d->tdx->stopConnection();
}

//! New connection slot.
/*! 
 *  This method is called whenever a client connects to the
 *  server. Its socket is stored for later processing.
 */

void tstMainWindow::onNewConnection(void)
{
    QTcpSocket *clientSocket = d->server->nextPendingConnection();
    
    d->sockets << clientSocket;

    d->clients->append(clientSocket->peerAddress().toString());
}
