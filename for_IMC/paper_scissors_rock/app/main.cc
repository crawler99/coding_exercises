#include "game.h"
#include "random_player.h"
#include "smart_player.h"

int main()
{
    psr::Rule rule;
    psr::PSRGame game(rule, 20);
    game.AddPlayer(new psr::RandomPlayer("Random_Player_1"));
    game.AddPlayer(new psr::RandomPlayer("Random_Player_2"));
    game.AddPlayer(new psr::SmartPlayer("Smart_Player_1", 5));
    game.Play();
    return 0;
}

