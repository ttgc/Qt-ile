#include <vector>
#include <string>
#include <sstream>
#include "titlescreen.h"
#define HIGH_SCORE_MAX 10
#define BUTTON_FONT "AutoREALM Mentelin"
#define LABEL_FONT "Cooper Black"

using namespace std;

TitleScreen::TitleScreen(QWidget *parent) : QWidget(parent)
{
    //setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+"/logo.png"));
    setWindowTitle("Qt-ile");
    setFixedSize(800,600);

    ranking = vector<StoredPlayer*>();
    for (unsigned int i(0);i<HIGH_SCORE_MAX;i++)
    {
        ranking.push_back(new StoredPlayer("Unknown"));
    }

    play_button = new QPushButton("PLAY",this);
    play_button->setFont(QFont(BUTTON_FONT,16,QFont::Bold,false));
    play_button->setCursor(Qt::PointingHandCursor);
    connect(play_button,SIGNAL(clicked()),this,SLOT(launchGame()));

    pseudo_field = new QLineEdit(this);
    pseudo_field->setFont(QFont(LABEL_FONT,18));
    pseudo_field->setMaxLength(12);
    pseudo_field->setAlignment(Qt::AlignCenter);

    high_scores = new QLabel(this);
    high_scores->setFont(QFont(LABEL_FONT,14));
    high_scores->setAlignment(Qt::AlignCenter);

    game_container = new GameContainer(this);
    player = new Player(game_container,"Anonymous");
    connect(player,SIGNAL(dead()),this,SLOT(endGame()));
    connect(player,SIGNAL(changedLane()),player,SLOT(redraw()));

    showTitleScreen();
}

TitleScreen::~TitleScreen()
{
    for (unsigned int i(0);i<ranking.size();i++)
    {
        delete ranking[i];
        ranking[i] = NULL;
    }
    ranking.clear();
}

void TitleScreen::showTitleScreen()
{
    stringstream builder("");
    for (unsigned int i(0);i<HIGH_SCORE_MAX;i++)
    {
        builder << ranking[i]->getPseudo() << " : " << ranking[i]->getScore() << endl;
    }
    high_scores->setText(QString::fromStdString(builder.str()));
    game_container->setGeometry(-1000,-1000,700,596);
    play_button->setGeometry(300,500,200,75);
    pseudo_field->setGeometry(300,400,200,64);
    high_scores->setGeometry(100,8,600,390);
    play_button->setShortcut(QKeySequence(tr("return")));

}

void TitleScreen::launchGame()
{
    QString pseudo = pseudo_field->text();
    if (pseudo == "")
    {
        pseudo = "Anonymous";
    }
    player->resetScore();
    player->setPseudo(pseudo.toStdString());
    play_button->setGeometry(-1000,-1000,200,75);
    pseudo_field->setGeometry(-1000,-1000,200,64);
    high_scores->setGeometry(-1000,-1000,600,390);
    game_container->setGeometry(50,2,700,596);
    play_button->setShortcut(NULL);
    player->setGeometry(250,550,249,45);
    player->setFocusPolicy(Qt::StrongFocus);
    player->setFocus();
    game_container->startTicking();
}

void TitleScreen::updateGame()
{
    game_container->checkCollision(player);
    player->increaseScore(game_container->getSpeed()*10);
}

void TitleScreen::endGame()
{
    game_container->stopTicking();
    if (player->getScore() > ranking[HIGH_SCORE_MAX-1]->getScore())
    {
        bool inserted(false);
        for (unsigned int i(HIGH_SCORE_MAX-1);i>0;i--)
        {
            if (ranking[i-1]->getScore() > player->getScore())
            {
                ranking.insert(ranking.begin()+i,new StoredPlayer(player));
                inserted = true;
                break;
            }
        }
        if (!inserted)
        {
            ranking.insert(ranking.begin(),new StoredPlayer(player));
        }
        delete ranking[HIGH_SCORE_MAX];
        ranking.pop_back();
    }
    showTitleScreen();
}
