#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_SCISSORS_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_SCISSORS_PLAYER_H_

#include "player.h"

namespace psr {

class ScissorsPlayer : public PSRPlayer
{
    public:
        ScissorsPlayer(const std::string &name) : PSRPlayer(name)
        {
        }

        Choice GetChoice() override
        {
            return Choice::Scissors;
        }
};

}

#endif
