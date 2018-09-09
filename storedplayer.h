#ifndef STOREDPLAYER_H
#define STOREDPLAYER_H
#include <string>

class Player;

class StoredPlayer
{
    public:
        StoredPlayer(std::string const& name);
        StoredPlayer(Player* const pl);
        int getScore() const {return score;}
        std::string getPseudo() const {return pseudo;}
    protected:
        int score;
        std::string pseudo;
};

#endif // STOREDPLAYER_H
