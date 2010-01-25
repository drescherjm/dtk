/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 25 12:24:58 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 25 12:25:01 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstMainWindow.h"

#include <dtkVr/dtkDeviceWii.h>
#include <dtkVr/dtkDeviceWiiAccelerationView.h>
#include <dtkVr/dtkDeviceWiiJoystickMotionView.h>
#include <dtkVr/dtkDeviceWiiInfraredMotionView.h>

#include <dtkVr/dtkDeviceTdx.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// tstMainWindowPrivate
// /////////////////////////////////////////////////////////////////

class tstMainWindowPrivate
{
public:
    static void joystickMotionHandler1(int x, int y);
    static void joystickMotionHandler2(int x, int y);

    static void remoteAccelerationHandler1(int x, int y, int z);
    static void remoteAccelerationHandler2(int x, int y, int z);

    static void nunchukAccelerationHandler1(int x, int y, int z);
    static void nunchukAccelerationHandler2(int x, int y, int z);

    static void infraredCursorMotionHandler1(float x, float y);
    static void infraredCursorMotionHandler2(float x, float y);

    static void infraredSingleMotionHandler1(float x, float y, float s, int n);
    static void infraredSingleMotionHandler2(float x, float y, float s, int n);

    static void tdxHandler1(float tx, float ty, float tz, float rx, float ry, float rz);
    static void tdxHandler2(float tx, float ty, float tz, float rx, float ry, float rz);

    static tstMainWindowPrivate *self;

public:
    dtkDeviceWii *device;
    dtkDeviceWiiJoystickMotionScene *joystickMotionScene;
    dtkDeviceWiiInfraredMotionScene *infraredMotionScene;
    dtkDeviceWiiJoystickMotionView *joystickMotionView;
    dtkDeviceWiiInfraredMotionView *infraredMotionView;
    dtkDeviceWiiAccelerationScene *remoteAccelerationScene;
    dtkDeviceWiiAccelerationScene *nunchukAccelerationScene;
    dtkDeviceWiiAccelerationView *remoteAccelerationView;
    dtkDeviceWiiAccelerationView *nunchukAccelerationView;

    dtkDeviceTdx *tdx;

public:
    QAction *switchToWiiAction;
    QAction *switchToTdxAction;

    QStackedWidget *stack;
};

void tstMainWindowPrivate::joystickMotionHandler1(int x, int y)
{
    self->joystickMotionScene->update(x, y);
}

void tstMainWindowPrivate::joystickMotionHandler2(int x, int y)
{
    qDebug() << __func__ << x << y;
}

void tstMainWindowPrivate::remoteAccelerationHandler1(int x, int y, int z)
{
    qDebug() << __func__ << x << y << z;
}

void tstMainWindowPrivate::remoteAccelerationHandler2(int x, int y, int z)
{
    qDebug() << __func__ << x << y << z;
}

void tstMainWindowPrivate::nunchukAccelerationHandler1(int x, int y, int z)
{
    qDebug() << __func__ << x << y << z;
}

void tstMainWindowPrivate::nunchukAccelerationHandler2(int x, int y, int z)
{
    qDebug() << __func__ << x << y << z;
}

void tstMainWindowPrivate::infraredCursorMotionHandler1(float x, float y)
{
    self->infraredMotionScene->update(x, y);
}

void tstMainWindowPrivate::infraredCursorMotionHandler2(float x, float y)
{
    qDebug() << __func__ << x << y;
}

void tstMainWindowPrivate::infraredSingleMotionHandler1(float x, float y, float s, int n)
{
    self->infraredMotionScene->update(x, y, s, n);
}

void tstMainWindowPrivate::infraredSingleMotionHandler2(float x, float y, float s, int n)
{
    qDebug() << __func__ << x << y << s << n;
}

void tstMainWindowPrivate::tdxHandler1(float tx, float ty, float tz, float rx, float ry, float rz)
{
    qDebug() << __func__ << tx << ty << tz << rx << ry << rz;
}

void tstMainWindowPrivate::tdxHandler2(float tx, float ty, float tz, float rx, float ry, float rz)
{
    qDebug() << __func__ << tx << ty << tz << rx << ry << rz;
}

tstMainWindowPrivate *tstMainWindowPrivate::self = NULL;

// /////////////////////////////////////////////////////////////////
// tstMainWindow
// /////////////////////////////////////////////////////////////////

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent), d(new tstMainWindowPrivate)
{
    d->self = d;

    // /////////////////////////////////////////////////////////////////
    // wii page
    // /////////////////////////////////////////////////////////////////

    d->device = new dtkDeviceWii;

    d->device->registerJoystickMotionHandler(tstMainWindowPrivate::joystickMotionHandler1);
    d->device->registerJoystickMotionHandler(tstMainWindowPrivate::joystickMotionHandler2);
    d->device->registerRemoteAccelerationHandler(tstMainWindowPrivate::remoteAccelerationHandler1);
    d->device->registerRemoteAccelerationHandler(tstMainWindowPrivate::remoteAccelerationHandler2);
    d->device->registerNunchukAccelerationHandler(tstMainWindowPrivate::nunchukAccelerationHandler1);
    d->device->registerNunchukAccelerationHandler(tstMainWindowPrivate::nunchukAccelerationHandler2);
    d->device->registerInfraredCursorMotionHandler(tstMainWindowPrivate::infraredCursorMotionHandler1);
    d->device->registerInfraredCursorMotionHandler(tstMainWindowPrivate::infraredCursorMotionHandler2);
    d->device->registerInfraredSingleMotionHandler(tstMainWindowPrivate::infraredSingleMotionHandler1);
    d->device->registerInfraredSingleMotionHandler(tstMainWindowPrivate::infraredSingleMotionHandler2);

    connect(d->device, SIGNAL(discovered()), this, SLOT(onDeviceDiscovered()));
    connect(d->device, SIGNAL(buttonPressed(dtkDeviceWii::dtkDeviceWiiButton)), this, SLOT(onDeviceButtonPressed(dtkDeviceWii::dtkDeviceWiiButton)));
    connect(d->device, SIGNAL(buttonReleased(dtkDeviceWii::dtkDeviceWiiButton)), this, SLOT(onDeviceButtonReleased(dtkDeviceWii::dtkDeviceWiiButton)));

    d->joystickMotionScene = new dtkDeviceWiiJoystickMotionScene;
    d->joystickMotionView = new dtkDeviceWiiJoystickMotionView;
    d->joystickMotionView->setScene(d->joystickMotionScene);
    d->joystickMotionView->setWindowFlags(Qt::Tool);

    d->infraredMotionScene = new dtkDeviceWiiInfraredMotionScene;
    d->infraredMotionView = new dtkDeviceWiiInfraredMotionView;
    d->infraredMotionView->setScene(d->infraredMotionScene);
    d->infraredMotionView->setWindowFlags(Qt::Tool);

    d->remoteAccelerationScene = new dtkDeviceWiiAccelerationScene;
    d->remoteAccelerationView = new dtkDeviceWiiAccelerationView;
    d->remoteAccelerationView->setScene(d->remoteAccelerationScene);
    d->remoteAccelerationView->setWindowFlags(Qt::Tool);

    d->nunchukAccelerationScene = new dtkDeviceWiiAccelerationScene;
    d->nunchukAccelerationView = new dtkDeviceWiiAccelerationView;
    d->nunchukAccelerationView->setScene(d->nunchukAccelerationScene);
    d->nunchukAccelerationView->setWindowFlags(Qt::Tool);

    QWidget *wiiWidget = new QWidget(this);

    QPushButton *startDiscoveryButton = new QPushButton("Start", wiiWidget);
    QPushButton  *stopDiscoveryButton = new QPushButton( "Stop", wiiWidget);

    QHBoxLayout *discoveryLayout = new QHBoxLayout;
    discoveryLayout->addWidget(startDiscoveryButton);
    discoveryLayout->addWidget(stopDiscoveryButton);

    connect(startDiscoveryButton, SIGNAL(clicked()), this, SLOT(onStartDiscoveryButtonClicked()));
    connect( stopDiscoveryButton, SIGNAL(clicked()), this, SLOT( onStopDiscoveryButtonClicked()));

    QCheckBox *led1CheckBox = new QCheckBox(this);
    QCheckBox *led2CheckBox = new QCheckBox(this);
    QCheckBox *led3CheckBox = new QCheckBox(this);
    QCheckBox *led4CheckBox = new QCheckBox(this);

    QHBoxLayout *ledLayout = new QHBoxLayout;
    ledLayout->addWidget(led1CheckBox);
    ledLayout->addWidget(led2CheckBox);
    ledLayout->addWidget(led3CheckBox);
    ledLayout->addWidget(led4CheckBox);

    connect(led1CheckBox, SIGNAL(toggled(bool)), this, SLOT(onLed1CheckBoxToggled(bool)));
    connect(led2CheckBox, SIGNAL(toggled(bool)), this, SLOT(onLed2CheckBoxToggled(bool)));
    connect(led3CheckBox, SIGNAL(toggled(bool)), this, SLOT(onLed3CheckBoxToggled(bool)));
    connect(led4CheckBox, SIGNAL(toggled(bool)), this, SLOT(onLed4CheckBoxToggled(bool)));

    QCheckBox *irsCheckBox = new QCheckBox(this);

    connect(irsCheckBox, SIGNAL(toggled(bool)), this, SLOT(onInfraredSensorCheckBoxToggled(bool)));

    QCheckBox *forceFeedbackCheckBox = new QCheckBox(this);

    connect(forceFeedbackCheckBox, SIGNAL(toggled(bool)), this, SLOT(onForceFeedBackCheckBoxToggled(bool)));

    QCheckBox *motionSensorCheckBox = new QCheckBox(this);

    connect(motionSensorCheckBox, SIGNAL(toggled(bool)), this, SLOT(onMotionSensorCheckBoxToggled(bool)));

    QCheckBox *expansionPortCheckBox = new QCheckBox(this);

    connect(expansionPortCheckBox, SIGNAL(toggled(bool)), this, SLOT(onExpansionPortCheckBoxToggled(bool)));

    QFormLayout *layout = new QFormLayout(wiiWidget);
    layout->addRow("Hardware discovery:", discoveryLayout);
    layout->addRow("Led display:", ledLayout);
    layout->addRow("Infrared sensors:", irsCheckBox);
    layout->addRow("Force feedback:", forceFeedbackCheckBox);
    layout->addRow("Motion sensors:", motionSensorCheckBox);
    layout->addRow("Expansion port:", expansionPortCheckBox);
    
    // /////////////////////////////////////////////////////////////////
    // space explorer page
    // /////////////////////////////////////////////////////////////////

    d->tdx = new dtkDeviceTdx;

    d->tdx->registerHandler(tstMainWindowPrivate::tdxHandler1);
    d->tdx->registerHandler(tstMainWindowPrivate::tdxHandler2);

    connect(d->tdx, SIGNAL(buttonPressed(dtkDeviceTdx::dtkDeviceTdxButton)), this, SLOT(onTdxDeviceButtonPressed(dtkDeviceTdx::dtkDeviceTdxButton)));
    connect(d->tdx, SIGNAL(buttonReleased(dtkDeviceTdx::dtkDeviceTdxButton)), this, SLOT(onTdxDeviceButtonReleased(dtkDeviceTdx::dtkDeviceTdxButton)));

    QWidget *tdxWidget = new QWidget(this);
    
    QPushButton *startTdxConnectionButton = new QPushButton(   "Connect", tdxWidget);
    QPushButton  *stopTdxConnectionButton = new QPushButton("Disconnect", tdxWidget);

    QHBoxLayout *tdxConnectionLayout = new QHBoxLayout;
    tdxConnectionLayout->addWidget(startTdxConnectionButton);
    tdxConnectionLayout->addWidget(stopTdxConnectionButton);

    QVBoxLayout *tdxLayout = new QVBoxLayout(tdxWidget);
    tdxLayout->addLayout(tdxConnectionLayout);

    connect(startTdxConnectionButton, SIGNAL(clicked()), this, SLOT(onStartTdxConnectionButtonClicked()));
    connect( stopTdxConnectionButton, SIGNAL(clicked()), this, SLOT( onStopTdxConnectionButtonClicked()));    

    // /////////////////////////////////////////////////////////////////
    // stack
    // /////////////////////////////////////////////////////////////////    

    d->switchToWiiAction = new QAction(QIcon(":/pixmaps/dtkDeviceWii.png"), "Wii", this);
    d->switchToWiiAction->setEnabled(false);

    d->switchToTdxAction = new QAction(QIcon(":/pixmaps/dtkDeviceTdx.png"), "Tdx", this);

    connect(d->switchToWiiAction, SIGNAL(triggered()), this, SLOT(switchToWii()));
    connect(d->switchToTdxAction, SIGNAL(triggered()), this, SLOT(switchToTdx()));

    d->stack = new QStackedWidget(this);
    d->stack->addWidget(wiiWidget);
    d->stack->addWidget(tdxWidget);

    QToolBar *toolbar = this->addToolBar("Devices");
    toolbar->addAction(d->switchToWiiAction);
    toolbar->addAction(d->switchToTdxAction);
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    this->setCentralWidget(d->stack);
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("dtkVr");
}

tstMainWindow::~tstMainWindow(void)
{
    delete d->device;
    delete d;

    d = NULL;
}

void tstMainWindow::switchToWii(void)
{
    d->stack->setCurrentIndex(0);

    d->switchToWiiAction->setEnabled(false);
    d->switchToTdxAction->setEnabled(true);
}

void tstMainWindow::switchToTdx(void)
{
    d->stack->setCurrentIndex(1);

    d->switchToWiiAction->setEnabled(true);
    d->switchToTdxAction->setEnabled(false);
}

// /////////////////////////////////////////////////////////////////
// Wii Slots to the device
// /////////////////////////////////////////////////////////////////

void tstMainWindow::onStartDiscoveryButtonClicked(void)
{
    d->device->startDiscovery();

    this->statusBar()->showMessage("Press 1 and 2 simultaneously", 1000);
}

void tstMainWindow::onStopDiscoveryButtonClicked(void)
{
    d->device->stopDiscovery();
}

void tstMainWindow::onLed1CheckBoxToggled(bool checked)
{
    d->device->toggleLed1(checked);
}

void tstMainWindow::onLed2CheckBoxToggled(bool checked)
{
    d->device->toggleLed2(checked);
}

void tstMainWindow::onLed3CheckBoxToggled(bool checked)
{
    d->device->toggleLed3(checked);
}

void tstMainWindow::onLed4CheckBoxToggled(bool checked)
{
    d->device->toggleLed4(checked);
}

void tstMainWindow::onInfraredSensorCheckBoxToggled(bool checked)
{
    d->device->toggleInfraredSensor(checked);

    d->infraredMotionView->setVisible(checked);
}

void tstMainWindow::onForceFeedBackCheckBoxToggled(bool checked)
{
    d->device->toggleForceFeedBack(checked);
}

void tstMainWindow::onMotionSensorCheckBoxToggled(bool checked)
{
    d->device->toggleMotionSensor(checked);

    d->remoteAccelerationView->setVisible(checked);
}

void tstMainWindow::onExpansionPortCheckBoxToggled(bool checked)
{
    d->device->toggleExpansionPort(checked);

         d->joystickMotionView->setVisible(checked);
    d->nunchukAccelerationView->setVisible(checked);
}

// /////////////////////////////////////////////////////////////////
// Slots from the device
// /////////////////////////////////////////////////////////////////

void tstMainWindow::onDeviceDiscovered(void)
{
    this->statusBar()->showMessage(QString("Discovered %1").arg(d->device->description()), 1000);
}

void tstMainWindow::onDeviceButtonPressed(dtkDeviceWii::dtkDeviceWiiButton button)
{
    if(button == dtkDeviceWii::dtkDeviceWiiButtonA)
        this->statusBar()->showMessage("Button A pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonB)
        this->statusBar()->showMessage("Button B pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonC)
        this->statusBar()->showMessage("Button C pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonZ)
        this->statusBar()->showMessage("Button Z pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonOne)
        this->statusBar()->showMessage("Button 1 pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonTwo)
        this->statusBar()->showMessage("Button 2 pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonMinus)
        this->statusBar()->showMessage("Button - pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonPlus)
        this->statusBar()->showMessage("Button + pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonUp)
        this->statusBar()->showMessage("Button Up pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonDown)
        this->statusBar()->showMessage("Button Down pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonLeft)
        this->statusBar()->showMessage("Button Left pressed", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonRight)
        this->statusBar()->showMessage("Button Right pressed", 1000);
}

void tstMainWindow::onDeviceButtonReleased(dtkDeviceWii::dtkDeviceWiiButton button)
{
    if(button == dtkDeviceWii::dtkDeviceWiiButtonA)
        this->statusBar()->showMessage("Button A released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonB)
        this->statusBar()->showMessage("Button B released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonC)
        this->statusBar()->showMessage("Button C released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonZ)
        this->statusBar()->showMessage("Button Z released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonOne)
        this->statusBar()->showMessage("Button 1 released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonTwo)
        this->statusBar()->showMessage("Button 2 released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonMinus)
        this->statusBar()->showMessage("Button - released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonPlus)
        this->statusBar()->showMessage("Button + released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonUp)
        this->statusBar()->showMessage("Button Up released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonDown)
        this->statusBar()->showMessage("Button Down released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonLeft)
        this->statusBar()->showMessage("Button Left released", 1000);

    if(button == dtkDeviceWii::dtkDeviceWiiButtonRight)
        this->statusBar()->showMessage("Button Right released", 1000);
}

// /////////////////////////////////////////////////////////////////
// Tdx Slots to the device
// /////////////////////////////////////////////////////////////////

void tstMainWindow::onStartTdxConnectionButtonClicked(void)
{
    d->tdx->startConnection();
}

void tstMainWindow::onStopTdxConnectionButtonClicked(void)
{
    d->tdx->stopConnection();
}

// /////////////////////////////////////////////////////////////////
// Tdx slots from the device
// /////////////////////////////////////////////////////////////////

void tstMainWindow::onTdxDeviceButtonPressed(dtkDeviceTdx::dtkDeviceTdxButton button)
{
    if(button == dtkDeviceTdx::dtkDeviceTdxButtonOne)
        this->statusBar()->showMessage("Button One pressed", 1000);

    if(button == dtkDeviceTdx::dtkDeviceTdxButtonTwo)
        this->statusBar()->showMessage("Button Two pressed", 1000);
}

void tstMainWindow::onTdxDeviceButtonReleased(dtkDeviceTdx::dtkDeviceTdxButton button)
{
    if(button == dtkDeviceTdx::dtkDeviceTdxButtonOne)
        this->statusBar()->showMessage("Button One released", 1000);

    if(button == dtkDeviceTdx::dtkDeviceTdxButtonTwo)
        this->statusBar()->showMessage("Button Two released", 1000);
}
