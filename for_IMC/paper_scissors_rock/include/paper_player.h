#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_PAPER_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_PAPER_PLAYER_H_

#include "player.h"

namespace psr {

class PaperPlayer : public PSRPlayer
{
    public:
        PaperPlayer(const std::string &name) : PSRPlayer(name)
        {
        }

        Choice GetChoice() override
        {
            return Choice::Paper;
        }
};

}

#endif
