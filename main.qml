import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Text {
        id: textText
        text: ""
        onTextChanged: {
            myStringObject.getString = textText.text;
            console.log("myStringObject.getString",myStringObject.getString,"myStringObject.sendStringListToQml()",myStringObject.sendStringListToQml())
        }
    }

    /*
     * 文本输入框
     * 字体对齐方式为右对齐
     * 超出文本框范围字符统统不显示
     * 隐藏问题：超出文本框的字符超出的宽度为随机宽度，具体根据字符的大小决定
     */
    Rectangle {
        id: textRectangle1
        x: 100
        width: 100
        height: 20

        border.width: 1
        border.color: "blue"
        clip: true
        TextInput {
            id: textRectangle1TextInput
            anchors.fill: parent
            text: "Hello"
            color: "green"
            readOnly: false
            verticalAlignment: Text.AlignVCenter
            selectionColor: "red"
            font.capitalization: Font.AllLowercase
        }
    }
    Rectangle {
        anchors.left: textRectangle1.right
        anchors.leftMargin: 2
        width: 20
        height: 20
        color: myMouseArea1.pressed ? "gray" : "black"
        radius: 40
        MouseArea {
            id: myMouseArea1
            anchors.fill: parent
            cursorShape: (containsMouse
                          ? (pressed
                             ? Qt.ClosedHandCursor
                             : Qt.OpenHandCursor)
                          : Qt.ArrowCursor);
            onPressed: {
                myStringObject.getString = textRectangle1TextInput.text
            }
        }
    }

    Component.onCompleted: {
    }
}
