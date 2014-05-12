
import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0

import dtkDistributed 1.0
import qml.jbQuick.Charts 1.0

import "status.js" as Status

ApplicationWindow {
    title: "DTK Distributed Dashboard"
    visible: true

    minimumHeight: 400
    minimumWidth: 600

    ListModel {
        id: choices
        ListElement { text: "http://localhost" }
        ListElement { text: "http://nef-devel.inria.fr" }
        ListElement { text: "http://sophia.grid5000.inria.fr" }
    }

    RowLayout {
        id: contentRow
        anchors.fill:parent
        anchors.margins: 8
        spacing: 16
        ColumnLayout {
            id: firstColumn
            Layout.minimumWidth: 400
            Layout.fillWidth: false
            RowLayout {
                id: statusrow
                ComboBox {
                    id: combo
                    editable: true
                    model: choices
                    currentIndex: 0
                    Layout.fillWidth: true
                    onAccepted: {
                        controller.deploy( choices.get(combo.currentIndex).text );
                        Status.show()
                    }
                }
                Button {
                    id: connectBotton
                    text: "Connect"
                    tooltip: "Deploy resource manager daemon on remote host"
                    onClicked: {
                        controller.deploy( choices.get(combo.currentIndex).text );
                        Status.show()
                    }
                }
                Button {
                    id: statusBotton
                    text: "Refresh"
                    tooltip:"Refresh status"
                    onClicked: {
                        Status.show()
                    }
                }
            }
            RowLayout {
                id: submitrow

                Label {
                    id: nodesLabel
                    text: "nodes:"
                }
                SpinBox {
                    id: nodes
                    minimumValue: 1
                    value: 1
                }

                Label {
                    id: coresLabel
                    /* Layout.fillWidth: true */
                    text: "cores:"
                }
                SpinBox {
                    id: cores
                    minimumValue: 1
                    value: 1
                }

                Button {
                    id: submitButton
                    text: "Submit"
                    Layout.fillWidth: true
                    tooltip: "Submit a job on a resource manager"
                    onClicked: {
                        console.debug("submit");
                        Status.submit(nodes.value, cores.value)
                    }
                }
            }
            RowLayout {
                id: jobs
                Item {
                    id: root
                    /* width: 600 */
                    /* height: 300 */
                    anchors.fill: parent
                    /* anchors.margins: Qt.platform.os === "osx" ? 12 : 6 */
                    ListModel {
                        id: jobModel
                    }

                    TableView{
                        model: jobModel
                        anchors.fill: parent

                        TableViewColumn {
                            role: "id"
                            title: "jobid"
                            width: 72
                            resizable: false
                            movable: false
                        }
                        TableViewColumn {
                            role: "user"
                            title: "User"
                            width: 100
                        }
                        TableViewColumn {
                            role: "nodes"
                            title: "Nodes"
                            width: 52
                        }
                        TableViewColumn {
                            role: "cores"
                            title: "Cores"
                            width: 52
                            visible: true
                        }
                        TableViewColumn {
                            role: "queue"
                            title: "Queue"
                            width: 100
                            visible: true
                        }
                    }
                }
            }
        }
        RowLayout {
            id: chartrow
            Chart {
                id: cores_pie;
                width: 200;
                height: 200;
                chartAnimated: true;
                chartAnimationEasing: Easing.InOutElastic;
                chartAnimationDuration: 2000;
                chartType: Charts.ChartType.PIE;
                chartData:  [];
            }
            Chart {
                id: nodes_pie;
                width: 200;
                height: 200;
                chartAnimated: true;
                chartAnimationEasing: Easing.InOutElastic;
                chartAnimationDuration: 2000;
                chartType: Charts.ChartType.DOUGHNUT;
                chartData:  [];
            }
        }
    }

    DistributedController {
        id: controller
    }
}
