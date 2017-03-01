#ifndef TETRIX3DSHAREDRESOURCES_H
#define TETRIX3DSHAREDRESOURCES_H

#include "tetrixpiece.h"
#include <QtCore/QMap>

namespace Qt3DRender {
    class QMaterial;
    class QMesh;
    class QAttribute;
}

class Tetrix3DSharedResources
{
public:
    static Tetrix3DSharedResources &instance();

    Qt3DRender::QMaterial *materialForShape(TetrixShape shape);
    Qt3DRender::QMesh *blockMesh();

private:
    Tetrix3DSharedResources();
    Tetrix3DSharedResources(Tetrix3DSharedResources const&);
    void operator =(Tetrix3DSharedResources const&);

    void initSharedResources();

    Qt3DRender::QMesh *m_blockMesh;
    QMap<TetrixShape, Qt3DRender::QMaterial *> m_shapeMaterials;
};

#endif // TETRIX3DSHAREDRESOURCES_H
