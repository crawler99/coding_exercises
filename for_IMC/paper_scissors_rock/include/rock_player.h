#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_ROCK_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_ROCK_PLAYER_H_

#include "player.h"

namespace psr {

class RockPlayer : public Player
{
    public:
        RockPlayer(const std::string &name) : Player(name)
        {
        }

        Choice GetChoice() override
        {
            return Choice::Rock;
        }
};

}

#endif
