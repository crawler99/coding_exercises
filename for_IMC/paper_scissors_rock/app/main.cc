#include "choice.h"

using namespace psr;

int main()
{
    PSRRule rule;
    PSRGame game(rule, 10);
    game.AddPlayer(new PSRRandomPlayer("Random_Player_1"));
    game.AddPlayer(new PSRRandomPlayer("Random_Player_2"));
    game.Play();
    return 0;
}

