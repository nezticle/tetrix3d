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

}
