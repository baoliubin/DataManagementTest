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
            myStringObject.loopData();
        }
    }
    property int num: 0
    Timer {
        running: true
        interval: 1000
        repeat: num < 5
        onTriggered: {
            textText.text = num.toString();

            num++;
        }
    }

    Component.onCompleted: {
        textText.text = "aaa";
    }
}
