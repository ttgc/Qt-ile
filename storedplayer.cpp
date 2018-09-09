#include "player.h"
#include "storedplayer.h"

using namespace std;

StoredPlayer::StoredPlayer(string const& name):score(0),pseudo(name)
{
    //do nothing
}

StoredPlayer::StoredPlayer(Player* const pl)
{
    pseudo = pl->pseudo;
    score = pl->score;
}
