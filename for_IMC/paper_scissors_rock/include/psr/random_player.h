#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_PSR_RANDOM_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_PSR_RANDOM_PLAYER_H_

#include <psr/player.h>
#include <cstdlib>
#include <ctime>

namespace psr {

/** This is a player who makes random choice each time. */
class RandomPlayer : public Player
{
    public:
        RandomPlayer(const std::string &name) : Player(name)
        {
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
