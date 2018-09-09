#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H
#include "player.h"
#include <QPushButton>
#include <QFrame>

class GameContainer : public QFrame
{
    Q_OBJECT

    public:
        GameContainer(QWidget *parent);
        void increaseSpeed();
        bool checkCollision(Player* pl) const;
        void startTicking();
        void stopTicking();
        void generate();
        double getSpeed() const {return speed;}
    public slots:
        void tickEvent();
    private:
        double speed;
        std::vector<QPushButton*> obstacles;
        QTimer* timer;
        int delta;
        double cumulspeed;
};

#endif // GAMECONTAINER_H
