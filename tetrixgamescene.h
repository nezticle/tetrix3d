#ifndef TETRIXGAMESCENE_H
#define TETRIXGAMESCENE_H

#include <QtCore/QObject>
#include <QtCore/QSize>

#include <Qt3DCore/QEntity>

namespace Qt3DRender {
    class QCamera;
}

class TetrixBoard;
class TetrixGameScene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QEntity* rootEntity READ rootEntity CONSTANT)
    Q_PROPERTY(QSize viewportSize READ viewportSize WRITE setViewportSize NOTIFY viewportSizeChanged)
    Q_PROPERTY(Qt3DRender::QCamera* camera READ camera CONSTANT)
    Q_PROPERTY(TetrixBoard* board READ board CONSTANT)
public:
    explicit TetrixGameScene(QObject *parent = 0);
    ~TetrixGameScene();

    Qt3DCore::QEntity* rootEntity() const;
    QSize viewportSize() const;
    Qt3DRender::QCamera* camera() const;
    TetrixBoard* board() const;

signals:
    void viewportSizeChanged(QSize viewportSize);

public slots:
    void setViewportSize(QSize viewportSize);

private:
    void createPlayArea();

    Qt3DCore::QEntity* m_rootEntity;
    QSize m_viewportSize;
    Qt3DRender::QCamera* m_camera;
    TetrixBoard *m_board;
};

#endif // TETRIXGAMESCENE_H
