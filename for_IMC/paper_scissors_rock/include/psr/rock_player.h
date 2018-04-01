#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_PSR_ROCK_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_PSR_ROCK_PLAYER_H_

#include <psr/player.h>

namespace psr {

/** This is a player who always show Rock. */
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
