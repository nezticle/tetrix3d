#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtGui/QOpenGLContext>
#include <QtGui/QSurfaceFormat>

#include "tetrixgamescene.h"
#include "tetrixboard.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    app.setOrganizationName("Bsquask");
    app.setOrganizationDomain("qad.io");
    app.setApplicationName("Tetrix3D");

//    QSurfaceFormat format;
//    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
//        format.setProfile(QSurfaceFormat::CoreProfile);
//    }
//    format.setDepthBufferSize(24);
//    format.setStencilBufferSize(8);
//    format.setSamples(0);
//    QSurfaceFormat::setDefaultFormat(format);

    //Expose QML objects here
    qmlRegisterType<TetrixGameScene>("io.qad.tetrix3d", 1, 0, "TetrixGameScene");
    qmlRegisterUncreatableType<TetrixBoard>("io.qad.tetrix3d", 1, 0, "TetrixBoard", "Created by TetrixGameScene");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
