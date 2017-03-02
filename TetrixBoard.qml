import QtQuick.Scene3D 2.0
import Qt3D.Core 2.0
import QtQuick 2.8
import io.qad.tetrix3d 1.0

Item {
    id: board

    property alias tetrixScene: gameScene
    property alias tetrixGame: gameScene.board

    Scene3D {
        id: sceneItem
        anchors.fill: board
        entity: gameScene.rootEntity
    }

    TetrixGameScene {
        id: gameScene
        viewportSize: Qt.size(sceneItem.width, sceneItem.height);
    }

    focus: true
    Keys.onPressed: {
        if (event.key === Qt.Key_Left) {
            gameScene.board.actionLeft();
            event.accepted = true;
        } else if (event.key === Qt.Key_Right) {
            gameScene.board.actionRight();
            event.accepted = true;
        } else if (event.key === Qt.Key_Up) {
            gameScene.board.actionUp();
            event.accepted = true;
        } else if (event.key === Qt.Key_Down) {
            gameScene.board.actionDown();
            event.accepted = true;
        } else if (event.key === Qt.Key_Space) {
            gameScene.board.actionDrop();
            event.accepted = true;
        } else if (event.key === Qt.Key_D ) {
            gameScene.board.actionDropOne();
            event.accepted = true;
        }
    }
}
