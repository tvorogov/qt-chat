import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.0
import qt.ClientBackend 1.0






Window {


//    ClientBackend {
//        id: backend

//    }


    StackView {

        id: stackView

        anchors.fill: parent
        focus: true
        initialItem: mainChatWindowStackComponent



    }
    Component{
        id: loginWindowStackComponent
        LoginWindow {}
    }

    Component {
        id: mainChatWindowStackComponent
        MainChatWindow {

        }

    }
}
