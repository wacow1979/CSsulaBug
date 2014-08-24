﻿import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

import "qrc:/ui" as UI

Rectangle{

    id: comicDetail

    width: 400
    height: 520

    visible: false
    color: "transparent"

    property variant comicInfo: {"key": "", "coverUrl": "", "name":"", "site": "", "type": "", "author":"", "lastUpdated":""}
    property int startY

    function startEnterAnimation(comicInfo, startY)
    {
        comicDetail.comicInfo = comicInfo;
        comicDetail.startY = startY;
        comicDetail.state = "MovingState";
    }

    function startLeaveAnimation()
    {
        comicDetail.state = "StartingState";
    }

    function onDownloadButtonClicked(comicKey, chapters){}

    state: "StartingState"

    states:[
        State {
            name: "StartingState"
            PropertyChanges { target: comicDetail; visible: false }
            PropertyChanges { target: chapterControl; visible: false }
        },

        State {
            name: "MovingState"
            PropertyChanges { target: comicDetail; visible: true }
            PropertyChanges { target: downloadButton; enabled: false; }
        },

        State {
            name: "ShowingState"
            PropertyChanges { target: comicDetail; visible: true }
            PropertyChanges { target: chapterControl; visible: true }
            PropertyChanges { target: downloadButton; enabled: true; }
        }
    ]

    transitions: [
        Transition {
            from: "StartingState"
            to: "MovingState"
            SequentialAnimation{
                PropertyAction { target: comicInfoItem; property:"y"; value:comicDetail.startY; }
                NumberAnimation { target: comicInfoItem; property: "y"; to: 0; duration: 200; easing.type: Easing.OutExpo }
                ScriptAction { script: {prepareChapterInfo(); comicDetail.state = "ShowingState"}}
            }
        },

        Transition {
            from: "MovingState"
            to: "ShowingState"
            NumberAnimation { target: chapterControl; property: "y"; to: comicInfoItem.height; duration: 500; easing.type: Easing.OutExpo }
        },

        Transition {
            from: "ShowingState"
            to: "StartingState"
            SequentialAnimation {
                NumberAnimation { target: chapterControl; property: "y"; to: comicInfoItem.height-chapterControl.height; duration: 500; easing.type: Easing.OutExpo }
                PropertyAction { target: chapterControl; property:"visible"; value:false; }
                NumberAnimation { target: comicInfoItem; property: "y"; to: comicDetail.startY; duration: 200; easing.type: Easing.OutExpo }
                PropertyAction { target: comicDetail; property:"visible"; value:false; }
            }
        }
    ]

    /*
    SequentialAnimation {
        id: enterAnimation
        PropertyAction { target: comicInfoItem; property:"y"; value:comicDetail.startY; }
        PropertyAction { target: comicDetail; property:"visible"; value:true; }
        NumberAnimation { target: comicInfoItem; property: "y"; to: 0; duration: 200; easing.type: Easing.OutExpo }
        ScriptAction { script: prepareChapterInfo()}
        PropertyAction { target: chapterControl; property:"visible"; value:true;}
        NumberAnimation { target: chapterControl; property: "y"; to: comicInfoItem.height; duration: 500; easing.type: Easing.OutExpo }
    }

    SequentialAnimation {
        id: leaveAnimation
        NumberAnimation { target: chapterControl; property: "y"; to: comicInfoItem.height-chapterControl.height; duration: 500; easing.type: Easing.OutExpo }
        PropertyAction { target: chapterControl; property:"visible"; value:false; }
        NumberAnimation { target: comicInfoItem; property: "y"; to: comicDetail.startY; duration: 200; easing.type: Easing.OutExpo }
        PropertyAction { target: comicDetail; property:"visible"; value:false; }
    }*/

    function prepareChapterInfo()
    {
        chapterModel.clear();
        chapterGrid.selectedChapters = {};

        var chapterNames = service.getChapterNames(comicDetail.comicInfo.key);
        for (var i = 0; i < chapterNames.length; i++)
        {
           chapterGrid.selectedChapters[chapterNames[i]] = true;
           chapterModel.append({"chapter": chapterNames[i]});
        }

        chapterGrid.selectedChaptersChanged();
    }

    UI.ComicInfoItem{
        id: comicInfoItem

        z: 1

        width: parent.width
        height: 120

        comicInfo: comicDetail.comicInfo
        highlight: true

        Button{

            id: downloadButton

            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 10

            text: "下載"

            onClicked:{
                var selectedChapters = []
                for(var chapter in chapterGrid.selectedChapters)
                {
                    if(chapterGrid.selectedChapters[chapter])
                    {
                        selectedChapters.push(chapter);
                    }
                }

                onDownloadButtonClicked(comicInfo.key, selectedChapters);
            }
        }
    }

    Rectangle {
        id: chapterControl

        width: parent.width
        height: comicDetail.height - comicInfoItem.height

        y: comicInfoItem.height-chapterControl.height;

        visible: false
        color: "transparent"

        Rectangle{
            id: selectionControl

            width: parent.width
            height: 40

            color: "#006064"

            Row{
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10

                spacing: 10

                Button{
                    text: "全選"
                    onClicked: {
                        for(var chapter in chapterGrid.selectedChapters)
                        {
                            chapterGrid.selectedChapters[chapter] = true;
                        }
                        chapterGrid.selectedChaptersChanged();
                    }
                }

                Button{
                    text: "取消全選"
                    onClicked: {
                        for(var chapter in chapterGrid.selectedChapters)
                        {
                            chapterGrid.selectedChapters[chapter] = false;
                        }
                        chapterGrid.selectedChaptersChanged();
                    }
                }

                Text {
                    id: selectedMessage

                    anchors.verticalCenter: parent.verticalCenter
                    Layout.fillWidth: parent

                    color:  "#f5f5f5"

                    Connections {
                        target: chapterGrid
                        onSelectedChaptersChanged: {
                            var count = 0;
                            for(var chapter in chapterGrid.selectedChapters)
                            {
                                count += chapterGrid.selectedChapters[chapter] ? 1 : 0;
                            }

                            selectedMessage.text = "已選擇了 " + count + " 話";
                        }
                    }
                }
            }
        }

        GridView{
            id: chapterGrid

            property var selectedChapters: ({})

            anchors.top: selectionControl.bottom
            anchors.bottom: parent.bottom

            width: parent.width

            cellWidth: 100
            cellHeight: 40

            model: ListModel {
                id: chapterModel
            }

            delegate: Rectangle{
                id: chapter

                width: chapterGrid.cellWidth
                height: chapterGrid.cellHeight

                color: "#00bcd4"

                Connections {
                    target: chapterGrid
                    onSelectedChaptersChanged: {
                        chapter.color = chapterGrid.selectedChapters[chapterName.text] ? "#00bcd4" : "#f5f5f5";
                    }
                }

                Text{
                    id:chapterName
                    anchors.centerIn: parent
                    text: model.chapter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        chapterGrid.selectedChapters[chapterName.text] = !chapterGrid.selectedChapters[chapterName.text];
                        chapterGrid.selectedChaptersChanged();
                    }
                }
            }
        }
    }
}
