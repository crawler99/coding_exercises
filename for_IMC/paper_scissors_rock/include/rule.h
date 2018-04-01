#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_RULE_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_RULE_H_

enum class Judgement
{
    Win, Draw, Lose
};

template <typename ChoiceT>
class Rule
{
    public:
        virtual Judgement Judge(const ChoiceT &first, const ChoiceT &second) const = 0;
};

namespace psr {

enum class Choice
{
    Paper, Scissors, Rock
};

class Rule : public ::Rule<Choice>
{
    public:
        Judgement Judge(const Choice &first, const Choice &second) const override;
};

}

#endif
