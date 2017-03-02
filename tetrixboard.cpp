#include "tetrixboard.h"
#include <QtCore/QTimerEvent>
#include <QtCore/QCoreApplication>

TetrixBoard::TetrixBoard(Qt3DCore::QEntity *parentEntity, QObject *parent)
    : QObject(parent)
    , m_score(0)
    , m_level(1)
    , m_linesRemoved(0)
    , m_piecesDropped(0)
{
    m_board.resize(BoardWidth * BoardHeight);
    m_blocks.resize(BoardWidth * BoardHeight);

    m_isStarted = false;
    m_isPaused = false;
    clearBoard();

    for (int y = 0; y < BoardHeight; ++y) {
        for (int x = 0; x < BoardWidth; ++x) {
            m_blocks[BoardWidth * y + x] = (new TetrixPieceEntity(x, y, parentEntity));
        }
    }

    m_nextPiece.setRandomShape();
}

TetrixBoard::~TetrixBoard()
{

}

void TetrixBoard::start()
{
    if (m_isPaused)
        return;

    m_isStarted = true;
    m_isWaitingAfterLine = false;
    m_piecesDropped = 0;
    setLinesRemoved(0);
    setScore(0);
    setLevel(1);
    clearBoard();

    newPiece();
    m_timer.start(timeoutTime(), this);
}

void TetrixBoard::pause()
{
    if (!m_isStarted)
        return;

    m_isPaused = !m_isPaused;
    if (m_isPaused)
        m_timer.stop();
    else
        m_timer.start(timeoutTime(), this);

}

int TetrixBoard::score() const
{
    return m_score;
}

int TetrixBoard::level() const
{
    return m_level;
}

int TetrixBoard::linesRemoved() const
{
    return m_linesRemoved;
}

bool TetrixBoard::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest) {
        updateEntitites();
        return true;
    }

    return QObject::event(event);
}

void TetrixBoard::setScore(int score)
{
    if (m_score == score)
        return;

    m_score = score;
    emit scoreChanged(score);
}

void TetrixBoard::setLevel(int level)
{
    if (m_level == level)
        return;

    m_level = level;
    emit levelChanged(level);
}

void TetrixBoard::setLinesRemoved(int linesRemoved)
{
    if (m_linesRemoved == linesRemoved)
        return;

    m_linesRemoved = linesRemoved;
    emit linesRemovedChanged(linesRemoved);
}

void TetrixBoard::actionLeft()
{
    tryMove(m_curPiece, m_curX - 1, m_curY);
}

void TetrixBoard::actionRight()
{
    tryMove(m_curPiece, m_curX + 1, m_curY);
}

void TetrixBoard::actionUp()
{
    tryMove(m_curPiece.rotatedRight(), m_curX, m_curY);
}

void TetrixBoard::actionDown()
{
    tryMove(m_curPiece.rotatedLeft(), m_curX, m_curY);
}

void TetrixBoard::actionDrop()
{
    dropDown();
}

void TetrixBoard::actionDropOne()
{
    oneLineDown();
}

void TetrixBoard::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timer.timerId()) {
        if (m_isWaitingAfterLine) {
            m_isWaitingAfterLine = false;
            newPiece();
            m_timer.start(timeoutTime(), this);
        } else {
            oneLineDown();
        }
    } else {
        QObject::timerEvent(event);
    }
}

void TetrixBoard::update()
{
    QEvent *updateRequest = new QEvent(QEvent::UpdateRequest);
    QCoreApplication::postEvent(this, updateRequest);
}

void TetrixBoard::updateEntitites()
{
    // Go through each position and update blocks
    for (int i = 0; i < BoardHeight; ++i) {
        for (int j = 0; j < BoardWidth; ++j) {
            //TetrixShape shape = shapeAt(j, BoardHeight - i - 1);
            TetrixShape shape = shapeAt(j, i);
            auto entity = m_blocks[(i * BoardWidth) + j];
            if (shape != NoShape) {
                entity->setShape(shape);
                entity->setVisible(true);
            } else {
                entity->setVisible(false);
            }
        }
    }

    // Update current shape
    if (m_curPiece.shape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
            int x = m_curX + m_curPiece.x(i);
            int y = m_curY - m_curPiece.y(i);
            auto entity = m_blocks[(y * BoardWidth) + x];
            entity->setShape(m_curPiece.shape());
            entity->setVisible(true);
        }
    }
}

void TetrixBoard::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        m_board[i] = NoShape;
}

void TetrixBoard::dropDown()
{
    int dropHeight = 0;
    int newY = m_curY;
    while (newY > 0) {
        if (!tryMove(m_curPiece, m_curX, newY - 1))
            break;
        --newY;
        ++dropHeight;
    }
    pieceDropped(dropHeight);
}

void TetrixBoard::oneLineDown()
{
    if (!tryMove(m_curPiece, m_curX, m_curY - 1))
        pieceDropped(0);
}

void TetrixBoard::pieceDropped(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = m_curX + m_curPiece.x(i);
        int y = m_curY - m_curPiece.y(i);
        shapeAt(x, y) = m_curPiece.shape();
    }

    ++m_piecesDropped;
    if (m_piecesDropped % 25 == 0) {
        setLevel(++m_level);
        m_timer.start(timeoutTime(), this);
    }

    setScore(m_score + dropHeight + 7);
    removeFullLines();

    if (!m_isWaitingAfterLine)
        newPiece();
}

void TetrixBoard::removeFullLines()
{
    int numFullLines = 0;

    for (int i = BoardHeight - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < BoardWidth; ++j) {
            if (shapeAt(j, i) == NoShape) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {

            ++numFullLines;
            for (int k = i; k < BoardHeight - 1; ++k) {
                for (int j = 0; j < BoardWidth; ++j)
                    shapeAt(j, k) = shapeAt(j, k + 1);
            }

            for (int j = 0; j < BoardWidth; ++j)
                shapeAt(j, BoardHeight - 1) = NoShape;
        }

    }

    if (numFullLines > 0) {
        setLinesRemoved(m_linesRemoved + numFullLines);
        setScore(m_score + 10 * numFullLines);

        m_timer.start(500, this);
        m_isWaitingAfterLine = true;
        m_curPiece.setShape(NoShape);
        update();
    }
}

void TetrixBoard::newPiece()
{
    m_curPiece = m_nextPiece;
    m_nextPiece.setRandomShape();
    //showNextPiece();
    m_curX = BoardWidth / 2 + 1;
    m_curY = BoardHeight - 1 + m_curPiece.minY();

    if (!tryMove(m_curPiece, m_curX, m_curY)) {
        m_curPiece.setShape(NoShape);
        m_timer.stop();
        m_isStarted = false;
    }
}

bool TetrixBoard::tryMove(const TetrixPiece &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }

    m_curPiece = newPiece;
    m_curX = newX;
    m_curY = newY;
    update();
    return true;
}
