import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0
import qt.ClientBackend 1.0


Window{

    width: 300
    height: 300
    visible: true
    title: "login"



    ColumnLayout {

        anchors.horizontalCenter: parent.horizontalCenter


        TextField {
            placeholderText: "username"



            id:username

        }




        TextField {
            placeholderText: "password"
            id:password
        }


        Label {
            text: "placeHolder"
        }


        RowLayout {

            Button {

                id:btn_singup

                text: "Sign up"
            }

            Button {



                id:btn_login

                text: "Log in"

                palette {
                    button: "green"
                }

                onClicked: {




                    backend.logined(username.text,password.text)
                    
                    
                    

//                    stackView.push(mainChatWindowStackComponent)

                }
            }

        }


    }

    function setTextLabael() {
        console.log("zxczxc")
    }
}


