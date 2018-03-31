#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_RANDOM_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_RANDOM_PLAYER_H_

#include "player.h"
#include <cstdlib>
#include <ctime>

namespace psr {

class RandomPlayer : public Player<Choice>
{
    public:
        RandomPlayer(const std::string &name) : Player<Choice>(name)
        {
            srand(time(nullptr));
        }

        Choice GetChoice() override
        {
            switch (rand() % 3)
            {
                case 0:
                    return Choice::Paper;
                case 1:
                    return Choice::Scissors;
                default:
                    return Choice::Rock;
            }
        }
};

}

#endif
