#include "tetrixpieceentity.h"
#include "tetrix3dsharedresources.h"

#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QMaterial>

TetrixPieceEntity::TetrixPieceEntity(int x, int y, Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity (parent)
    , m_xPos(x)
    , m_yPos(y)
    , m_visible(false)
{
    //Transform
    auto tranform = new Qt3DCore::QTransform(this);
    tranform->setTranslation(QVector3D(m_xPos, m_yPos, 0));
    addComponent(tranform);

    //Mesh
    addComponent(Tetrix3DSharedResources::instance().blockMesh());

    //Material
    m_material = Tetrix3DSharedResources::instance().materialForShape(NoShape);
    addComponent(m_material);

    //Enabled
    setEnabled(m_visible);
}

int TetrixPieceEntity::xPos() const
{
    return m_xPos;
}

int TetrixPieceEntity::yPos() const
{
    return m_yPos;
}

bool TetrixPieceEntity::visible() const
{
    return m_visible;
}

void TetrixPieceEntity::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    m_visible = visible;
    setEnabled(visible);
}

void TetrixPieceEntity::setShape(TetrixShape shape)
{
    if (m_material)
        removeComponent(m_material);
    m_material = Tetrix3DSharedResources::instance().materialForShape(shape);
    if (m_material)
        addComponent(m_material);
}
