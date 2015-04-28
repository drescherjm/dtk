import QtQuick 2.0

Item {
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        opacity: 0.7
        radius: 10
        gradient: Gradient {
            GradientStop { position: 0; color: "#375c93" }
            /* GradientStop { position: 0; color: "#305e0f" } */
            /* GradientStop { position: 0.33; color: "#8bb92d" } */
            /* GradientStop { position: 0.45; color: "#8bb92d" } */
            /* GradientStop { position: 1; color: "#305e0f" } */
            GradientStop { position: 0.33; color: "#8ba1c0" }
            GradientStop { position: 0.45; color: "#8ba1c0" }
            GradientStop { position: 1; color: "#375c93" }
            /* GradientStop { position: 0.33; color: "#4b3db9" } */
            /* GradientStop { position: 0.45; color: "#8ba1c0" } */
            /* GradientStop { position: 1; color: "#375c93" } */
        }
    }
    /* ColorStrip { */
    /*     id: color3 */
    /*     /\* color: "#769452" *\/ */
    /*     color: "#8ba1c0" */
    /* } */
    /* ShaderEffectSource { */
    /*     id: colorTable3 */
    /*     sourceItem: color3 */
    /*     smooth: true */
    /* } */

    /* ColorStrip { */
    /*     id: color4 */
    /*     /\* color: "#577c31" *\/ */
    /*     color: "#eeeeff" */
    /* } */
    /* ShaderEffectSource { */
    /*     id: colorTable4 */
    /*     sourceItem: color4 */
    /*     smooth: true */
    /* } */
    /* Swirl { */
    /*     width: parent.width */
    /*     anchors.bottom: parent.bottom */
    /*     height: parent.height / 8 */
    /*     opacity: 0.3 */
    /*     speed: 0.5 */
    /*     colorTable: colorTable3 */
    /* } */

    /* Swirl { */
    /*     width: parent.width */
    /*     anchors.bottom: parent.bottom */
    /*     height: parent.height / 6 */
    /*     opacity: 0.3 */
    /*     speed: 1 */
    /*     colorTable: colorTable4 */
    /* } */

    /* Image { */
    /*     id: inriaLogo */
    /*     source: "inria.png" */
    /*     width: 404 / 1.5 */
    /*     height: 145 / 1.5 */
    /*     anchors.bottom: parent.bottom */
    /*     anchors.right: parent.right */
    /*     anchors.margins: 10 */
    /* } */

    /* Image { */
    /*     id: dtklogo */
    /*     source: "dtk-logo.png" */

    /*     anchors.bottom: parent.bottom */
    /*     anchors.left: parent.left */
    /*     anchors.margins: 10 */
    /* } */
}
