#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_CHOICE_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_CHOICE_H_

#include <cstdlib>
#include <ctime>
#include <deque>
#include <map>
#include <set>
#include <numeric>
#include <memory>
#include <iostream>

namespace psr {

enum class JudgeRst
{
    Win, Draw, Lose
};

template <class T>
class Rule
{
    public:
        virtual JudgeRst Judge(const T &first, const T &second) const = 0;
};

template <class T>
class Player
{
    public:
        Player(const std::string &name) : _name(name) {}

        const std::string& GetName() { return _name; }

        virtual T GetChoice() = 0;

        void OnJudgement(JudgeRst judge_rst, std::map<T, uint32_t> &observation)
        {
            std::string judge_rst_str = (judge_rst == JudgeRst::Win) ? "Win" : (judge_rst == JudgeRst::Lose) ? "Lose" : "Draw";
            std::cout << "Player " << GetName() << " got a " << judge_rst_str << std::endl;
            ++_results[judge_rst];
            UpdateStrategy(judge_rst, observation);
        }

        uint32_t GetRstNum(JudgeRst judge_rst)
        {
            return _results[judge_rst];
        }

        virtual void UpdateStrategy(JudgeRst judge_rst, std::map<T, uint32_t> &observation)
        {
        }

        virtual bool DecideToQuit()
        {
            return false; // Default to play forever if the Game doesn't stop.
        }

    private:
        std::string _name;
        std::map<JudgeRst, uint32_t> _results;
};

enum class Choice
{
    Paper, Scissors, Rock
};

class PSRRule : public Rule<Choice>
{
    public:
        JudgeRst Judge(const Choice &first, const Choice &second) const override
        {
            switch (first)
            {
                case Choice::Paper:
                        return (second == Choice::Rock) ? JudgeRst::Win :
                            (second == Choice::Scissors) ? JudgeRst::Lose : JudgeRst::Draw;
                case Choice::Scissors:
                        return (second == Choice::Paper) ? JudgeRst::Win :
                            (second == Choice::Rock) ? JudgeRst::Lose : JudgeRst::Draw;
                case Choice::Rock:
                        return (second == Choice::Scissors) ? JudgeRst::Win :
                            (second == Choice::Paper) ? JudgeRst::Lose : JudgeRst::Draw;
                default:
                        return JudgeRst::Draw;  // Cannot reach here, but let's return a draw.
            }
        }
};

class PSRPaperPlayer : public Player<Choice>
{
    public:
        PSRPaperPlayer(const std::string &name) : Player<Choice>(name)
        {
        }

        Choice GetChoice() override
        {
            return Choice::Paper;
        }
};

class PSRScissorsPlayer : public Player<Choice>
{
    public:
        PSRScissorsPlayer(const std::string &name) : Player<Choice>(name)
        {
        }

        Choice GetChoice() override
        {
            return Choice::Scissors;
        }
};

class PSRRockPlayer : public Player<Choice>
{
    public:
        PSRRockPlayer(const std::string &name) : Player<Choice>(name)
        {
        }

        Choice GetChoice() override
        {
            return Choice::Rock;
        }
};

class PSRRandomPlayer : public Player<Choice>
{
    public:
        PSRRandomPlayer(const std::string &name) : Player<Choice>(name)
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

class PSRSmartPlayer : public Player<Choice>
{
    public:
        PSRSmartPlayer(const std::string &name, uint32_t observe_window)
            : Player<Choice>(name), _observe_window(observe_window)
        {
        }

        void UpdateStrategy(JudgeRst judge_rst, std::map<Choice, uint32_t> &observation) override
        {
            if (_paper_queue.size() == _observe_window)
            {
                _paper_queue.pop_front();
                _scissors_queue.pop_front();
                _rock_queue.pop_front();
            }

            _paper_queue.push_back(observation[Choice::Paper]);
            _scissors_queue.push_back(observation[Choice::Scissors]);
            _rock_queue.push_back(observation[Choice::Rock]);
        }

        Choice GetChoice() override
        {
            uint32_t paper_num = std::accumulate(_paper_queue.begin(), _paper_queue.end(), 0);
            uint32_t scissors_num = std::accumulate(_scissors_queue.begin(), _scissors_queue.end(), 0);
            uint32_t rock_num = std::accumulate(_rock_queue.begin(), _rock_queue.end(), 0);

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

template <class T>
class Game
{
    public:
        Game(const Rule<T> &rule, uint32_t rounds = -1) : _rule(rule), _rounds(rounds)
        {
        }

        void AddPlayer(Player<T> *player)
        {
            _players.insert(player);
        }

        void CleanPlayers()
        {
            _players.clear();
        }

        void Play()
        {
            uint32_t cur_round = 1;
            bool stop = false;
            while (!stop && (_rounds < 0 || cur_round <= _rounds))
            {
                std::cout << "==== Round ====" << cur_round << std::endl;

                if (_players.empty())
                {
                    continue;
                }

                std::map<T, uint32_t> choice_stats;
                std::map<T, std::set<Player<T>*>> choice_map;
                bool stop = false;

                for (auto &p : _players)
                {
                    T c = p->GetChoice();
                    std::cout << p->GetName() << " shows " << static_cast<int>(c) << std::endl;
                    ++choice_stats[c];
                    choice_map[c].insert(p);
                    if (p->DecideToQuit())
                    {
                        stop = true;
                    }
                }

                if (choice_map.size() == 2)
                {
                    auto cit = choice_map.cbegin();
                    T c1 = cit->first;
                    ++cit;
                    T c2 = cit->first;
                    auto judge1 = _rule.Judge(c1, c2);
                    auto judge2 = _rule.Judge(c2, c1);
                    for (const auto &p : choice_map[c1])
                    {
                        p->OnJudgement(judge1, choice_stats);
                    }
                    for (const auto &p : choice_map[c2])
                    {
                        p->OnJudgement(judge2, choice_stats);
                    }
                }
                else
                {
                    for (auto &p : _players)
                    {
                        p->OnJudgement(JudgeRst::Draw, choice_stats);
                    }
                }
                ++cur_round;
            }
        }

    private:
        std::set<Player<T>*> _players;
        const Rule<T> &_rule;
        int32_t _rounds { -1 }; // -1 means infinite rounds
};

using PSRGame = Game<Choice>;

}

#endif
