#include "psr/game.h"
#include "psr/random_player.h"
#include "psr/smart_player.h"
#include "psr/screen_player.h"

int main()
{
    psr::Rule rule;
    psr::Game game(rule, 10);
    game.AddPlayer(new psr::RandomPlayer("Random_Player_1"));
    game.AddPlayer(new psr::RandomPlayer("Random_Player_2"));
    game.AddPlayer(new psr::SmartPlayer("Smart_Player_1", 5));
    game.AddPlayer(new psr::ScreenPlayer("You"));
    game.Play("2 random_players with 1 smart_player with you");
    return 0;
}

