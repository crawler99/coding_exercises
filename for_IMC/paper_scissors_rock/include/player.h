#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_PLAYER_H_

#include "rule.h"
#include <map>
#include <iostream>

template <typename ChoiceT>
class Player
{
    public:
        Player(const std::string &name) : _name(name)
        {
        }

        const std::string& GetName()
        {
            return _name;
        }

        virtual ChoiceT GetChoice() = 0;

        void OnJudgement(ChoiceT my_choice, Judgement judgement, std::map<ChoiceT, uint32_t> &observation)
        {
            ++_results[judgement];
            UpdateStrategy(my_choice, judgement, observation);
        }

        uint32_t GetResultNum(Judgement judgement)
        {
            return _results[judgement];
        }

        virtual void UpdateStrategy(ChoiceT my_choice, Judgement judgement, std::map<ChoiceT, uint32_t> &observation)
        {
        }

        virtual bool DecideToQuit()
        {
            return false; // Default to play forever if the game doesn't stop.
        }

    private:
        std::string _name;
        std::map<Judgement, uint32_t> _results;
};

namespace psr {

using Player = ::Player<Choice>;

}

#endif
