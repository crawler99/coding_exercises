#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_GAME_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_GAME_H_

#include "rule.h"
#include "player.h"
#include <map>
#include <set>
#include <memory>
#include <iostream>

template <typename ChoiceT>
class Game
{
    public:
        Game(const Rule<ChoiceT> &rule, uint32_t rounds = -1) : _rule(rule), _rounds(rounds)
        {
        }

        void AddPlayer(Player<ChoiceT> *player)
        {
            _players.insert(player);
        }

        void CleanPlayers()
        {
            _players.clear();
        }

        void Play(const std::string &name = "")
        {
            srand(time(nullptr));
            uint32_t cur_round = 1;

            std::cout << "** Start Game (" << name << ") **"<< std::endl;

            while (_rounds == -1 || cur_round <= _rounds)
            {
                std::cout << "~~ Round " << cur_round << " ~~"<< std::endl;

                if (_players.empty())
                {
                    continue;
                }

                // Collect input choices from each player
                std::map<ChoiceT, uint32_t> choice_stats;
                std::map<ChoiceT, std::set<Player<ChoiceT>*>> choice_map;
                bool stop = false;
                for (auto &p : _players)
                {
                    ChoiceT c = p->GetChoice();

                    if (p->DecideToQuit())
                    {
                        stop = true;
                        break;
                    }

                    ++choice_stats[c];
                    choice_map[c].insert(p);

                    std::cout << p->GetName() << ": " << static_cast<int>(c) << std::endl;
                }

                if (stop) break;

                // Make judgement
                if (choice_map.size() == 2) // Only when there're totally two different choices that we can have winners and losers.
                {
                    auto cit = choice_map.cbegin();
                    ChoiceT c1 = cit->first;
                    ++cit;
                    ChoiceT c2 = cit->first;
                    auto judge1 = _rule.Judge(c1, c2);
                    auto judge2 = _rule.Judge(c2, c1);
                    for (const auto &p : choice_map[c1])
                    {
                        p->OnJudgement(c1, judge1, choice_stats);
                    }
                    for (const auto &p : choice_map[c2])
                    {
                        p->OnJudgement(c2, judge2, choice_stats);
                    }
                }
                else // For all other situations, we get a draw for every player.
                {
                    for (const auto &pair : choice_map)
                    {
                        for (const auto &p : pair.second)
                        {
                            p->OnJudgement(pair.first, Judgement::Draw, choice_stats);
                        }
                    }
                }
                ++cur_round;
            }
        }

    private:
        std::set<Player<ChoiceT>*> _players;
        const Rule<ChoiceT> &_rule;
        int32_t _rounds { -1 }; // -1 means infinite rounds
};

namespace psr {

using Game = ::Game<Choice>;

}

#endif
