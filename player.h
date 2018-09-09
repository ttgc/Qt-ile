#ifndef PLAYER_H
#define PLAYER_H
#include <QLabel>
#include "storedplayer.h"

enum Lane {LEFT=0,MIDDLE=250,RIGHT=500};

class Player : public QLabel, public StoredPlayer
{
    Q_OBJECT

    public:
        Player(QWidget *parent, std::string const& name);
        void increaseScore(int value);
        void keyPressEvent(QKeyEvent *ev);
        void kill();
        void resetScore();
        void setPseudo(std::string const& new_pseudo) {pseudo = new_pseudo;}
    public slots:
        void redraw();
    signals:
        void dead();
        void changedLane();
    private:
        Lane position;
};

#endif // PLAYER_H
