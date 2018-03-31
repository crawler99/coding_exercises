#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_SCISSORS_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_SCISSORS_PLAYER_H_

#include "player.h"

namespace psr {

class ScissorsPlayer : public Player
{
    public:
        ScissorsPlayer(const std::string &name) : Player(name)
        {
        }

        Choice GetChoice() override
        {
            return Choice::Scissors;
        }
};

}

#endif
