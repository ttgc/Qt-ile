#include <QKeyEvent>
#include <string>
#include "player.h"

using namespace std;

Player::Player(QWidget *parent, string const& name):QLabel(parent),StoredPlayer(name),position(MIDDLE)
{
    //setPixmap(QPixmap(QCoreApplication::applicationDirPath()+"/player.png"));
}

void Player::increaseScore(int value)
{
    score += value;
}

void Player::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Left)
    {
        switch (position) {
        case MIDDLE:
            position = LEFT;
            emit changedLane();
            break;
        case RIGHT:
            position = MIDDLE;
            emit changedLane();
            break;
        case LEFT: break;
        }
    }
    else if (ev->key() == Qt::Key_Right)
    {
        switch (position) {
        case MIDDLE:
            position = RIGHT;
            emit changedLane();
            break;
        case LEFT:
            position = MIDDLE;
            emit changedLane();
            break;
        case RIGHT: break;
        }
    }
    else if (ev->key() == Qt::Key_Escape)
    {
        kill();
    }
}

void Player::kill()
{
    emit dead();
}

void Player::resetScore()
{
    score = 0;
}

void Player::redraw()
{
    setGeometry(position,550,249,45);
}
