#ifndef TITLESCREEN_H
#define TITLESCREEN_H
#include "storedplayer.h"
#include "player.h"
#include <QtWidgets>

class TitleScreen : public QWidget
{
    Q_OBJECT

    public:
        TitleScreen(QWidget *parent = 0);
        ~TitleScreen();
        void showTitleScreen();

    public slots:
        void launchGame();
        void endGame();

    private:
        QPushButton* play_button;
        QLineEdit* pseudo_field;
        QLabel* high_scores;
        QFrame* game_container;
        Player* player;
        std::vector<StoredPlayer*> ranking;
};

#endif // TITLESCREEN_H
