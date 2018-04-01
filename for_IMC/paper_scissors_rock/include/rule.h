#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_RULE_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_RULE_H_

enum class Judgement
{
    Win, Draw, Lose
};

/** This is the absctraction of a game rule.
 *  For a Paper-Scissors-Rock-like game, we only need two pre-condtions to play it:
 *      1) There's a judging rule that can sperate all players exactly to two sides.
 *      2) The same judging rule can decide which side wins.
 */
template <typename ChoiceT>
class Rule
{
    public:
        virtual Judgement Judge(const ChoiceT &first, const ChoiceT &second) const = 0;
};

#endif
