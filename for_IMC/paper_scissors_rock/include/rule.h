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

#endif
