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
                text: "Instructions: \n Left and Right -> Move Piece\n Up and Down -> Rotate Piece\n Space -> Drop Piece\n D -> Drop One"
            }

            Button {
                text: "Start"
                focusPolicy: Qt.NoFocus
                onClicked: {
                    board.tetrixGame.start();
                }
            }
            Button {
                text: "Pause"
                focusPolicy: Qt.NoFocus
                onClicked: {
                    board.tetrixGame.pause();
                }
            }
            Button {
                text: "Quit"
                focusPolicy: Qt.NoFocus
                onClicked: {
                    window.close();
                }
            }
        }
    }

}
