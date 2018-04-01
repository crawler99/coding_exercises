#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_RULE_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_RULE_H_

enum class Judgement
{
    Win, Draw, Lose
};

/** This is the absctraction of a game rule.
 *  For a Paper-Scissors-Rock-like game, the only win-lose case is all players togeher
 *  make exactly two kinds of choices, and there's a rule to judge which one wins.
 */
template <typename ChoiceT>
class Rule
{
    public:
        virtual Judgement Judge(const ChoiceT &first, const ChoiceT &second) const = 0;
};

#endif
