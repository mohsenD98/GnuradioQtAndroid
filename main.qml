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
        enabled: androidPermissions? androidPermissions.storagePermission && androidPermissions.usbPermission : false
        opacity: enabled ? 1 : 0.4

        Button{
            text: "detect device"
            onClicked: {
                flow.fd = "72"
                flow.usbPath = "/dev/bus/usb/001/002"
                flow.initial()
                log.text = "initializing blocks success@!"
            }
        }

        Button{
            text: "initize blocks"
            onClicked: {
                flow.fd = "72"
                flow.usbPath = "/dev/bus/usb/001/002"
                flow.initial()
                log.text = "initializing blocks success@!"
            }
        }

        Button{
            text: "connecting blocks"
            onClicked: {
                log.text = "connecting blocks"
                flow.connect()

            }
        }

        Button{
            text: "running blocks"
            onClicked: {
                log.text = "not developed"
            }
        }

        Button{
            text: "stop"
            onClicked: {
                log.text = "not developed"
            }
        }
    }
}
