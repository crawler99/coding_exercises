#include "choice.h"

using namespace psr;

int main()
{
    PSRRule rule;
    PSRGame game(rule, 20);
    game.AddPlayer(new PSRRandomPlayer("Random_Player_1"));
    game.AddPlayer(new PSRRandomPlayer("Random_Player_2"));
    game.AddPlayer(new PSRSmartPlayer("Smart_Player_1", 5));
    game.Play();
    return 0;
}

