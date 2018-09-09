#include <vector>
#include <QTimer>
#include "gamecontainer.h"
#define OBSTACLE_LENGTH 20

using namespace std;

GameContainer::GameContainer(QWidget *parent): QFrame(parent),speed(1.0),delta(0),cumulspeed(0.0)
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(tickEvent()));
    connect(timer,SIGNAL(timeout()),parent,SLOT(updateGame()));
    obstacles = vector<QPushButton*>();
    for (unsigned int i(0);i<OBSTACLE_LENGTH;i++)
    {
        QPushButton* but = new QPushButton(this);
        but->setGeometry(-1000,-1000,250,64);
        but->setDisabled(true);
        but->setHidden(true);
        but->setText("(╯°□°）╯︵ ┻━┻");
        obstacles.push_back(but);
    }
}

void GameContainer::increaseSpeed()
{
    if (speed < 4.0)
    {
        speed += 0.1;
    }
}

bool GameContainer::checkCollision(Player *pl) const
{
    for (unsigned int i(0);i<obstacles.size();i++)
    {
        if ((!obstacles[i]->isHidden()) && obstacles[i]->geometry().contains(pl->geometry(),false)) {
            pl->kill();
            return true;
        }
    }
    return false;
}

void GameContainer::startTicking()
{
    delta = 0;
    cumulspeed = 0.0;
    timer->start(33);
}

void GameContainer::stopTicking()
{
    timer->stop();
    for (unsigned int i(0);i<obstacles.size();i++)
    {
        obstacles[i]->setHidden(true);
    }
}

void GameContainer::generate()
{
    //
}

void GameContainer::tickEvent()
{
    delta++;
    cumulspeed += speed;
    while (cumulspeed >= 1.0)
    {
        for (unsigned int i(0);i<obstacles.size();i++)
        {
            if ((!obstacles[i]->isHidden()))
            {
                QRect hitbox(obstacles[i]->geometry());
                hitbox.moveBottom(hitbox.bottom()+1);
                obstacles[i]->setGeometry(hitbox);
            }
        }
        cumulspeed -= 1.0;
    }
    if (delta >= 30) {
        generate();
        increaseSpeed();
        delta -= 30;
    }
}
