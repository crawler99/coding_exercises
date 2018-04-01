#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_PSR_GAME_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_PSR_GAME_H_

#include <game.h>
#include <psr/rule.h>
#include <psr/player.h>

namespace psr {

class Game : public ::Game<Choice>
{
    public:
        Game(const Rule &rule, uint32_t rounds = -1) : ::Game<Choice>(rule, rounds)
        {
        }

        void PrintPlayerChoices(const std::map<Choice, std::set<Player*>> &choices) const override;
};

}

#endif
