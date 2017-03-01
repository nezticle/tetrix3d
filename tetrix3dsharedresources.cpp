#include "tetrix3dsharedresources.h"
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QPhongMaterial>

Tetrix3DSharedResources::Tetrix3DSharedResources()
{
    initSharedResources();
}

void Tetrix3DSharedResources::initSharedResources()
{
    m_blockMesh = new Qt3DRender::QMesh();
    m_blockMesh->setSource(QUrl("qrc:/roundCube.obj"));

    // Create material for each shape/color
    auto material = new Qt3DExtras::QPhongMaterial();
    material->setShininess(10.0f);
    material->setDiffuse(QColor(QRgb(0x000000)));
    m_shapeMaterials[TetrixShape::NoShape] = material;

    material = new Qt3DExtras::QPhongMaterial();
    material->setShininess(10.0f);
    material->setDiffuse(QColor(QRgb(0xCC6666)));
    m_shapeMaterials[TetrixShape::ZShape] = material;

    material = new Qt3DExtras::QPhongMaterial();
    material->setShininess(10.0f);
    material->setDiffuse(QColor(QRgb(0x66CC66)));
    m_shapeMaterials[TetrixShape::SShape] = material;

    material = new Qt3DExtras::QPhongMaterial();
    material->setShininess(10.0f);
    material->setDiffuse(QColor(QRgb(0x6666CC)));
    m_shapeMaterials[TetrixShape::LineShape] = material;

    material = new Qt3DExtras::QPhongMaterial();
    material->setShininess(10.0f);
    material->setDiffuse(QColor(QRgb(0xCCCC66)));
    m_shapeMaterials[TetrixShape::TShape] = material;

    material = new Qt3DExtras::QPhongMaterial();
    material->setShininess(10.0f);
    material->setDiffuse(QColor(QRgb(0xCC66CC)));
    m_shapeMaterials[TetrixShape::SquareShape] = material;

    material = new Qt3DExtras::QPhongMaterial();
    material->setShininess(10.0f);
    material->setDiffuse(QColor(QRgb(0x66CCCC)));
    m_shapeMaterials[TetrixShape::LShape] = material;

    material = new Qt3DExtras::QPhongMaterial();
    material->setShininess(10.0f);
    material->setDiffuse(QColor(QRgb(0xDAAA00)));
    m_shapeMaterials[TetrixShape::MirroredLShape] = material;
}

Tetrix3DSharedResources &Tetrix3DSharedResources::instance()
{
    static Tetrix3DSharedResources instance;
    return instance;
}

Qt3DRender::QMaterial *Tetrix3DSharedResources::materialForShape(TetrixShape shape)
{
    return m_shapeMaterials[shape];
}

Qt3DRender::QMesh *Tetrix3DSharedResources::blockMesh()
{
    return m_blockMesh;
}
