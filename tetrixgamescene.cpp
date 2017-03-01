#include "tetrixgamescene.h"
#include "tetrixboard.h"

#include <QtCore/QDebug>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QCamera>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QRenderSettings>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QDirectionalLight>

#include <Qt3DExtras/QCuboidMesh>

TetrixGameScene::TetrixGameScene(QObject *parent)
    : QObject(parent)
    , m_rootEntity(new Qt3DCore::QEntity())
    , m_viewportSize(QSize(480, 600))
    , m_board(new TetrixBoard(m_rootEntity, this))
{
    // Scene Camera
    m_camera = new Qt3DRender::QCamera(m_rootEntity);
    m_camera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    m_camera->setAspectRatio(static_cast<float>(m_viewportSize.width()) / static_cast<float>(m_viewportSize.height()));
    m_camera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    m_camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));
    m_camera->setPosition(QVector3D(0.0f, -50.0f, 25.0f));

    // Forward Renderer Framegraph
    Qt3DRender::QRenderSettings *frameGraphComponent = new Qt3DRender::QRenderSettings(m_rootEntity);
    Qt3DExtras::QForwardRenderer *forwardRenderer = new Qt3DExtras::QForwardRenderer();
    forwardRenderer->setCamera(m_camera);
    forwardRenderer->setClearColor(Qt::black);
    frameGraphComponent->setActiveFrameGraph(forwardRenderer);
    m_rootEntity->addComponent(frameGraphComponent);

    // Lighting
    auto *directionLightEntity = new Qt3DCore::QEntity(m_rootEntity);
    auto *directionalLight = new Qt3DRender::QDirectionalLight;
    directionLightEntity->addComponent(directionalLight);
    directionalLight->setWorldDirection(QVector3D(0.1f, 0.5f, -0.5f));
    directionalLight->setIntensity(1);

    // Game Objects
    createPlayArea();


    m_board->start();
}

TetrixGameScene::~TetrixGameScene()
{

}

Qt3DCore::QEntity *TetrixGameScene::rootEntity() const
{
    return m_rootEntity;
}

QSize TetrixGameScene::viewportSize() const
{
    return m_viewportSize;
}

Qt3DRender::QCamera *TetrixGameScene::camera() const
{
    return m_camera;
}

TetrixBoard *TetrixGameScene::board() const
{
    return m_board;
}

void TetrixGameScene::setViewportSize(QSize viewportSize)
{
    if (m_viewportSize == viewportSize)
        return;

    m_viewportSize = viewportSize;
    emit viewportSizeChanged(viewportSize);
}

void TetrixGameScene::createPlayArea()
{
    auto frameEntity = new Qt3DCore::QEntity(m_rootEntity);
    //Material
    auto framePhongMaterial = new Qt3DExtras::QPhongMaterial(frameEntity);
    framePhongMaterial->setDiffuse(QColor(70, 150, 56));
    framePhongMaterial->setShininess(10.0f);
    frameEntity->addComponent(framePhongMaterial);

    //Mesh
    auto frameMesh = new Qt3DRender::QMesh(frameEntity);
    frameMesh->setSource(QUrl("qrc:/frame.obj"));
    frameEntity->addComponent(frameMesh);
}
