#ifndef TETRIXPIECEENTITY_H
#define TETRIXPIECEENTITY_H

#include <Qt3DCore/QEntity>
#include <QtGui/QVector3D>

#include "tetrixpiece.h"

namespace Qt3DCore {
    class QTransform;
}

namespace Qt3DRender {
    class QMesh;
    class QMaterial;
    class QPickEvent;
}

class TetrixPieceEntity : public Qt3DCore::QEntity
{
public:
    TetrixPieceEntity(int x, int y, Qt3DCore::QNode *parent = 0);

    int xPos() const;
    int yPos() const;
    bool visible() const;

public slots:
    void setVisible(bool visible);
    void setShape(TetrixShape shape);

private:

    Qt3DRender::QMaterial *m_material;

    int m_xPos;
    int m_yPos;
    bool m_visible;
};

#endif // TETRIXPIECEENTITY_H
