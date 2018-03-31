#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_CHOICE_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_CHOICE_H_

namespace psr {

enum class JudgeRst
{
    Win, Draw, Lose
};

template <typename ChoiceT>
class Rule
{
    public:
        virtual JudgeRst Judge(const ChoiceT &first, const ChoiceT &second) const = 0;
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

}

#endif
