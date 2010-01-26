/* tstMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 25 12:24:08 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 25 13:26:45 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTMAINWINDOW_H
#define TSTMAINWINDOW_H

#include <dtkVr/dtkDeviceWii.h>
#include <dtkVr/dtkDeviceTdx.h>

#include <QtGui/QMainWindow>

class tstMainWindowPrivate;

class tstMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     tstMainWindow(QWidget *parent = 0);
    ~tstMainWindow(void);

public slots:
    void switchToWii(void);
    void switchToTdx(void);

// Wii

public slots: // Slots to the device
    void onStartDiscoveryButtonClicked(void);
    void  onStopDiscoveryButtonClicked(void);

    void onLed1CheckBoxToggled(bool);
    void onLed2CheckBoxToggled(bool);
    void onLed3CheckBoxToggled(bool);
    void onLed4CheckBoxToggled(bool);

    void onInfraredSensorCheckBoxToggled(bool);
    void onForceFeedBackCheckBoxToggled(bool);
    void onMotionSensorCheckBoxToggled(bool);
    void onExpansionPortCheckBoxToggled(bool);

protected slots: // Slots from the device
    void onDeviceDiscovered(void);
    void onDeviceButtonPressed(dtkDeviceWii::dtkDeviceWiiButton);
    void onDeviceButtonReleased(dtkDeviceWii::dtkDeviceWiiButton);

// Tdx

public slots: // Slots to the device
    void onStartTdxConnectionButtonClicked(void);
    void  onStopTdxConnectionButtonClicked(void);

protected slots: // Slots from the device
    void onTdxDeviceButtonPressed(dtkDeviceTdx::dtkDeviceTdxButton);
    void onTdxDeviceButtonReleased(dtkDeviceTdx::dtkDeviceTdxButton);

private:
    tstMainWindowPrivate *d;
};

#endif // TSTMAINWINDOW_H
