#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_PSR_PAPER_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_PSR_PAPER_PLAYER_H_

#include <psr/player.h>

namespace psr {

/** This is a player who always show Paper. */
class PaperPlayer : public Player
{
    public:
        PaperPlayer(const std::string &name) : Player(name)
        {
        }

        Choice GetChoice() override
        {
            return Choice::Paper;
        }
};

}

#endif
