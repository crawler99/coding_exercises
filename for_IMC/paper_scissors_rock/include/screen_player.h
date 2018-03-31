#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_SCREEN_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_SCREEN_PLAYER_H_

#include "player.h"
#include <cstdlib>
#include <ctime>

namespace psr {

class ScreenPlayer : public Player
{
    public:
        ScreenPlayer(const std::string &name) : Player(name)
        {
        }

        void UpdateStrategy(Choice my_choice, Judgement judgement, std::map<Choice, uint32_t> &observation) override
        {
            switch (judgement)
            {
                case Judgement::Win:
                    {
                        std::cout << "Congratulations! You got a win." << std::endl;
                        break;
                    }
                case Judgement::Lose:
                    {
                        std::cout << "Unfortunately, you lost this round." << std::endl;
                        break;
                    }
                case Judgement::Draw:
                    {
                        std::cout << "We had a draw in this round." << std::endl;
                        break;
                    }
                default:
                    ;
            }
            std::cout << "Total win[" << GetResultNum(Judgement::Win) << "], loss[" << GetResultNum(Judgement::Lose)
                      << "], draw[" << GetResultNum(Judgement::Draw) << "]" << std::endl;
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
