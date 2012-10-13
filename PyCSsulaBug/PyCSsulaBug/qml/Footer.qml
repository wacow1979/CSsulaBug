// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {

    id: footer
    anchors.bottom: parent.bottom
    width: parent.width
    height: 60
    radius: 0
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#847a7a"
        }

        GradientStop {
            position: 0.070
            color: "#693f71"
        }

        GradientStop {
            position: 1
            color: "#383244"
        }
    }


    Row {

        anchors.centerIn: parent
        spacing: 20

        Rectangle {
            id: exploreButton
            width: (footer.width / 3) * 0.8
            height: footer.height * 0.6
            radius: 10
            gradient: Gradient {
                GradientStop { position: 0; color: "#714f9c"}
                GradientStop { position: 0.500; color: "#312b3e"}
                GradientStop { position: 1; color: "#714f9c"}
            }

            Text {
                id: exploreText
                color: "#b5b5b5"
                text: "瀏覽漫畫"
                font.family: "微軟正黑體"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: false
                anchors.fill: parent
                font.pixelSize: 21
            }

        }

        Rectangle {
            id: settingButton
            width: (footer.width / 3) * 0.8
            height: footer.height * 0.6
            radius: 10

            gradient: Gradient {
                GradientStop { position: 0; color: "#714f9c"}
                GradientStop { position: 0.500; color: "#312b3e"}
                GradientStop { position: 1; color: "#714f9c"}
            }

            Text {
                id: settingText
                color:"#b5b5b5"
                text: "設定選項"
                font.family: "微軟正黑體"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: false
                anchors.fill: parent
                font.pixelSize: 21
            }
        }

        Rectangle {
            id: aboutButton
            width: (footer.width / 3) * 0.8
            height: footer.height * 0.6
            radius: 10

            gradient: Gradient {
                GradientStop { position: 0; color: "#714f9c"}
                GradientStop { position: 0.500; color: "#312b3e"}
                GradientStop { position: 1; color: "#714f9c"}
            }

            Text {
                id: aboutText
                color:"#b5b5b5"
                text: "關於軟體"
                font.family: "微軟正黑體"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: false
                anchors.fill: parent
                font.pixelSize: 21
            }

        }
    }
}