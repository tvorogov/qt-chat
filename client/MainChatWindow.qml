import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0
import qt.ClientBackend 1.0

Window {

    width: 640
    height: 480
    visible: true
    title: "Client"



    ClientBackend {
        id:backend

        onSomeMessage: {
            clietTextArea.append(msg)
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

                height: btn_connect.height
                border.color: "red"
                border.width: 1

                TextInput {
                    id: serverAddress

                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                    rightPadding: 10
                    width: parent.width

                    text: "192.168.60.9"






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

                width: btn_connect.width




                height: btn_connect.height
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
                id: btn_connect
                text: "Connect"

                onClicked: {
                    backend.connectClicked(serverAddress.text,portAddress.text)
//

                }

            }

            Button {
                id: btn_disconnect
                text: "Disconnect"
                onClicked: {
                    backend.disconnectClicked()
                }
            }
        }





        Rectangle {

            Layout.fillHeight: true
            Layout.fillWidth: true
            border.color: "green"
            border.width: 1

            TextArea {

                id:clietTextArea


                anchors.fill: parent

                readOnly: true
                wrapMode: TextInput.WrapAnywhere

                text: backend.recivedMessage
            }
        }

        RowLayout {

            Rectangle {

                Layout.fillWidth: true
                height: btn_send_message.height
                border.color: "red"
                border.width: 1


                TextInput {
                    id: msgTextInput

                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                    rightPadding: 10
                    width: parent.width
                }
            }

            Button {
                id: btn_send_message
                text: "send"

                onClicked: {
                    backend.sendMessageClicked(msgTextInput.text)
                }
            }
            Button {
                id: btn_send_file
                text: "send file"


                    FileDialog {
                        id:fileDialog
                        title: "choose a file"
                        folder: shortcuts.home

                        onAccepted: {


                            backend.sendFileClicked(fileDialog.fileUrls)

                            fileDialog.close()
                        }
                        onRejected: {
                            console.log("Canceled")
                            fileDialog.close()
                        }


                    }




                onClicked: {



                    fileDialog.open()


                }

            }
        }




    }



}
