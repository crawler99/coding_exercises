#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_SMART_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_SMART_PLAYER_H_

#include "player.h"
#include <deque>
#include <numeric>
#include <cstdlib>
#include <ctime>

namespace psr {

class SmartPlayer : public Player
{
    public:
        SmartPlayer(const std::string &name, uint32_t observe_window)
            : Player(name), _observe_window(observe_window)
        {
        }

        void UpdateStrategy(Choice my_choice, Judgement judgement, std::map<Choice, uint32_t> &observation) override
        {
            if (_paper_queue.size() == _observe_window)
            {
                _paper_queue.pop_front();
                _scissors_queue.pop_front();
                _rock_queue.pop_front();
            }

            uint32_t papers = observation[Choice::Paper];
            if (my_choice == Choice::Paper)
            {
                --papers;
            }
            uint32_t scissors = observation[Choice::Scissors];
            if (my_choice == Choice::Scissors)
            {
                --scissors;
            }
            uint32_t rocks = observation[Choice::Rock];
            if (my_choice == Choice::Rock)
            {
                --rocks;
            }

            _paper_queue.push_back(papers);
            _scissors_queue.push_back(scissors);
            _rock_queue.push_back(rocks);
        }

        Choice GetChoice() override
        {
            uint32_t paper_num = std::accumulate(_paper_queue.begin(), _paper_queue.end(), 0);
            uint32_t scissors_num = std::accumulate(_scissors_queue.begin(), _scissors_queue.end(), 0);
            uint32_t rock_num = std::accumulate(_rock_queue.begin(), _rock_queue.end(), 0);

            // If all three choices got the same number of occurrence in the observation window,
            // just generate a randome choice to show.
            if (paper_num == scissors_num && paper_num == rock_num)
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

            // Otherwise, there must be a most frequent historical choice. Generate next choice against to it.
            if (paper_num > rock_num && paper_num > scissors_num)
            {
                return Choice::Scissors;
            }
            else if (rock_num > scissors_num)
            {
                return Choice::Paper;
            }
            return Choice::Rock;
        }

    private:
        std::deque<uint32_t> _paper_queue;
        std::deque<uint32_t> _scissors_queue;
        std::deque<uint32_t> _rock_queue;
        uint32_t _observe_window { 10 };
};

}

#endif
