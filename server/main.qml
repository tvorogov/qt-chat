import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0
import qt.ServerBackend 1.0




Window {
//    width: 640
//    height: 480
    minimumHeight: 480
    minimumWidth: 640

    visible: true
    title: "server"



    ServerBackend {
        id: backend



        onNewMessage: {

            serverTextArea.append(msg)

        }
        onClientConnected: {
            serverTextArea.append("smd connected")
        }
        onClientDisconnected: {
            serverTextArea.append("smd disconnected")
        }

    }


    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        RowLayout {



            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                anchors.left: parent.left
                text: "IP Address"
            }

            Rectangle {

                Layout.fillWidth: true

                height: btn_start_server.height
                border.color: "red"
                border.width: 1

                TextInput {
                    id: serverAddress

                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                    rightPadding: 10
                    width: parent.width

                    text: backend.defServer()




                    onTextChanged: {

                        if (serverAddress.length > 15)
                            serverAddress.remove(15,16)
                    }
                }


            }


            Text {
                text: "Port"
            }

            Rectangle {

                width: btn_start_server.width




                height: btn_start_server.height
                border.color: "red"
                border.width: 1

                TextInput {
                    id: portAddress
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                    rightPadding: 10
                    width: parent.width

                    text: "90909"


                    onTextChanged: {
                        if (portAddress.length > 5)
                            portAddress.remove(5,6)
                    }
                }

            }

            Button {

                id: btn_start_server


                text: "start server"

                onClicked: {
                    backend.startServerClicked(serverAddress.text,portAddress.text);

                }

            }

            Button {



                id: btn_stop_server
                anchors.right: parent.right
                text: "stop server"

                onCanceled: {
                    backend.stopServerClicked()
                }
            }
        }

        Rectangle {

            Layout.fillHeight: true
            Layout.fillWidth: true

            border.color: "gray"
            border.width: 1



            TextArea {

                id:serverTextArea


                anchors.fill: parent

                readOnly: true
                wrapMode: TextInput.WrapAnywhere
            }

        }


    }



}
