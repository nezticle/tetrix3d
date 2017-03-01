#ifndef TETRIXBOARD_H
#define TETRIXBOARD_H

#include <QtCore/QObject>
#include <QtCore/QBasicTimer>

#include "tetrixpiece.h"
#include "tetrixpieceentity.h"

const int BoardHeight = 22;
const int BoardWidth = 10;

class TetrixBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged)
    Q_PROPERTY(int level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(int linesRemoved READ linesRemoved WRITE setLinesRemoved NOTIFY linesRemovedChanged)
public:
    explicit TetrixBoard(Qt3DCore::QEntity *parentEntity, QObject *parent = nullptr);
    ~TetrixBoard();

    int score() const;
    int level() const;
    int linesRemoved() const;

    bool event(QEvent *event) override;

public slots:
    void start();
    void pause();

    void setScore(int score);
    void setLevel(int level);
    void setLinesRemoved(int linesRemoved);

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int linesRemoved);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void update();
    void updateEntitites();

    TetrixShape &shapeAt(int x, int y) { return m_board[(y * BoardHeight) + x]; }
    int timeoutTime() { return 1000 / (1 + m_level); }
    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const TetrixPiece &newPiece, int newX, int newY);

    QBasicTimer m_timer;
    bool m_isStarted;
    bool m_isPaused;
    bool m_isWaitingAfterLine;
    TetrixPiece m_curPiece;
    TetrixPiece m_nextPiece;
    int m_curX;
    int m_curY;
    TetrixShape m_board[BoardWidth * BoardHeight];
    //TetrixPieceEntity *m_blocks[BoardWidth * BoardHeight];
    QVector<TetrixPieceEntity *> m_blocks;

    int m_score;
    int m_level;
    int m_linesRemoved;
    int m_piecesDropped;
};

#endif // TETRIXBOARD_H
