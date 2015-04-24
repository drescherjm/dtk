// modified from Clock.qml, see license at the end.


import QtQuick 2.0

Text {
    id: clock

    property real fontSize: parent.height * 0.05
    property int  times: 0
    property int  interval: 1000
    property int  duration: 15 * 60
    property color textColor: parent.textColor != undefined ? parent.textColor : "black"
    property string fontFamily: parent.fontFamily != undefined ? parent.fontFamily : "Helvetica"

    text: elapsedTime();
    function numToString(num, length) {
        var r = "" + num;
        while (r.length < length) {
            r = "0" + r;
        }
        return r;
    }
    function printElapsed(val) {
        return numToString(Math.floor(val / 60),2) + ":" + numToString(Math.floor(val % 60),2);
    }
    function elapsedTime() {
        var elapsed = times * interval /1000
        if (elapsed > duration * 0.7 && textColor != "red") { textColor = "orange" }
        if (elapsed > duration && textColor != "red") { textColor = "red" }
        times++
        return printElapsed(elapsed);
    }

    color: textColor;
    font.family: fontFamily;
    font.pixelSize: fontSize * 0.6;

    anchors.top: parent.top;
    anchors.left: parent.left;
    anchors.margins: font.pixelSize;

    Timer {
        id: timer
        interval: clock.interval;
        repeat: true;
        running: false
        onTriggered: clock.text = clock.elapsedTime();
    }
    Keys.onPressed:  {timer.start()}
}


/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QML Presentation System.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
