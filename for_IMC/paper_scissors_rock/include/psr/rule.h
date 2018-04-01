#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_PSR_RULE_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_PSR_RULE_H_

#include <rule.h>

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
