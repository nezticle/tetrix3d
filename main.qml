import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Tetrix3D")
    id: window

    TetrixBoard {
        id: board
        height: window.height
        width: window.width * 0.5
        anchors.left: window.left
    }

    Item {
        id: statusItems
        anchors.right: window.right
        anchors.left: board.right
        anchors.top: window.top
        anchors.bottom: window.bottom

        ColumnLayout {
            anchors.fill: parent
            RowLayout {
                Label {
                    text: "Score"
                }
                Label {
                    text: board.tetrixGame.score
                }
            }
            RowLayout {
                Label {
                    text: "Level"
                }
                Label {
                    text: board.tetrixGame.level
                }
            }
            RowLayout {
                Label {
                    text: "Lines Removed"
                }
                Label {
                    text: board.tetrixGame.linesRemoved
                }
            }
            Label {
                text: "Instuctions: \n Left and Right -> Move Piece\nUp and Down -> Rotate Piece\n Space -> Drop Piece"
            }

            Button {
                text: "Start"
                onClicked: {
                    board.tetrixGame.start();
                }
            }
            Button {
                text: "Pause"
                onClicked: {
                    board.tetrixGame.pause();
                }
            }
            Button {
                text: "Quit"
                onClicked: {
                    window.close();
                }
            }
        }
    }

}
