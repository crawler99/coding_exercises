#include <psr/rule.h>

namespace psr {

Judgement Rule::Judge(const Choice &first, const Choice &second) const
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

}
