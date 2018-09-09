#include <vector>
#include <cstdlib>
#include <ctime>
#include <QTimer>
#include "gamecontainer.h"
#define OBSTACLE_LENGTH 10

using namespace std;

GameContainer::GameContainer(QWidget *parent): QFrame(parent),speed(1.0),delta(0),cumulspeed(0.0)
{
    srand(time(NULL));
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
    int luck(rand()%100);
    if (luck < 35)
    {
        int lane(rand()%3);
        QRect* hitbox = new QRect();
        bool invalid(false);
        hitbox->setRect(lane*250,0,250,64);
        int id(-1);
        for (unsigned int i(0);i<obstacles.size();i++)
        {
            if (obstacles[i]->geometry().contains(*hitbox,false))
            {
                invalid = true;
            }
            if (obstacles[i]->isHidden())
            {
                id = i;
            }
        }
        if (!invalid && id >= 0)
        {
            obstacles[id]->setHidden(false);
            obstacles[id]->setGeometry(*hitbox);
        }
        else
        {
            delete hitbox;
        }
    }
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
                if (obstacles[i]->geometry().top() > 700)
                {
                    obstacles[i]->setHidden(true);
                    obstacles[i]->setGeometry(-1000,-1000,250,64);
                }
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
