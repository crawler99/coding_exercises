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
        Judgement Judge(const Choice &first, const Choice &second) const override
        {
            switch (first)
            {
                case Choice::Paper:
                        return (second == Choice::Rock) ? Judgement::Win :
                            (second == Choice::Scissors) ? Judgement::Lose : Judgement::Draw;
                case Choice::Scissors:
                        return (second == Choice::Paper) ? Judgement::Win :
                            (second == Choice::Rock) ? Judgement::Lose : Judgement::Draw;
                case Choice::Rock:
                        return (second == Choice::Scissors) ? Judgement::Win :
                            (second == Choice::Paper) ? Judgement::Lose : Judgement::Draw;
                default:
                        return Judgement::Draw;  // Cannot reach here, but let's return a draw.
            }
        }
};

}

#endif
