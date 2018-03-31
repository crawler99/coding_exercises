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
                        std::cout << "Congratulations! You got a win.";
                        break;
                    }
                case Judgement::Lose:
                    {
                        std::cout << "Unfortunately, you lost this round.";
                        break;
                    }
                case Judgement::Draw:
                    {
                        std::cout << "You got a draw in this round.";
                        break;
                    }
                default:
                    ;
            }
            std::cout << " (total win[" << GetResultNum(Judgement::Win) << "], loss[" << GetResultNum(Judgement::Lose)
                      << "], draw[" << GetResultNum(Judgement::Draw) << "])" << std::endl;
        }

        Choice GetChoice() override
        {
            PrintChoices();
            char c;
            std::cin >> c;
            switch (c)
            {
                case 'P': return Choice::Paper;
                case 'S': return Choice::Scissors;
                case 'R': return Choice::Rock;
                case 'E':
                    {
                        _exit = true;
                        return Choice::Rock; // Return whatever. It doesn't matter as the game will stop.
                    }
                default:
                    return GetChoice(); // Recursive call, should be acceptable for a screen player.
            }
        }

        bool DecideToQuit() override
        {
            return _exit;
        }

    private:
        void PrintChoices()
        {
            std::cout << "Make your choice:" << std::endl
                      << "[P]aper" << std::endl
                      << "[S]cissors" << std::endl
                      << "[R]ock" << std::endl
                      << "[E]xit" << std::endl
                      << "<= ";
        }

        bool _exit { false };
};

}

#endif
