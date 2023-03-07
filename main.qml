import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Text{
        id: log
        text: "log"
        anchors.centerIn: parent
        font.pixelSize: 18
        font.bold: true
    }

    Button{
        id: permissions
        text: "Permissions"
        onClicked: {
            log.text = "Granteed"
            androidPermissions.requestPermissions()
        }
    }
    Column{
        anchors.top: permissions.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        enabled: androidPermissions? (androidPermissions.storagePermission && androidPermissions.usbPermission) : false
        opacity: enabled ? 1 : 0.4

        Button{
            text: "initize blocks"
            onClicked: {
                log.text = "initializing"
                flow.initial()
            }
        }

        Button{
            text: "connecting blocks"
            onClicked: {
                log.text = "connecting"
                flow.connect()

            }
        }

        Button{
            text: "running blocks"
            onClicked: {
                log.text = "running"
                flow.start()
            }
        }

        Button{
            text: "stop"
            onClicked: {
                log.text = "stopping"
                flow.stop()
            }
        }
    }
}
