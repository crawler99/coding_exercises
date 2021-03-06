#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "psr/game.h"
#include "psr/paper_player.h"
#include "psr/scissors_player.h"
#include "psr/rock_player.h"
#include "psr/smart_player.h"

using namespace std;

TEST(PaperScissorsRock, Correctness)
{
    psr::Rule rule;
    psr::Game game(rule, 10);

    auto *paper_player = new psr::PaperPlayer("Player_Paper");
    auto *scissors_Player = new psr::ScissorsPlayer("Player_Scissors");
    auto *rock_player = new psr::RockPlayer("Player_Rock");

    // paper_player vs rock_layer, paper_player should always win.
    game.AddPlayer(paper_player);
    game.AddPlayer(rock_player);
    game.Play("paper_player vs rock_player");
    EXPECT_EQ(10, paper_player->GetResultNum(Judgement::Win));
    EXPECT_EQ(10, rock_player->GetResultNum(Judgement::Lose));

    // rock_player vs scissors_player, rock_layer should always win.
    game.CleanPlayers();
    game.AddPlayer(scissors_Player);
    game.AddPlayer(rock_player);
    game.Play("scissors_player vs rock_player");
    EXPECT_EQ(10, scissors_Player->GetResultNum(Judgement::Lose));
    EXPECT_EQ(10, rock_player->GetResultNum(Judgement::Win));

    // When three adamant players play together, they will always get a draw.
    game.AddPlayer(paper_player);
    game.Play("paper_player vs scissors_player vs rock_player");
    EXPECT_EQ(10, paper_player->GetResultNum(Judgement::Draw));
    EXPECT_EQ(10, scissors_Player->GetResultNum(Judgement::Draw));
    EXPECT_EQ(10, rock_player->GetResultNum(Judgement::Draw));

    // When a smart player plays with an adamant player, he will always win from the second round.
    game.CleanPlayers();
    game.AddPlayer(scissors_Player);
    auto *smart_player = new psr::SmartPlayer("Player_Smart", 3);
    game.AddPlayer(smart_player);
    game.Play("smart_player vs scissors_player");
    EXPECT_GE(smart_player->GetResultNum(Judgement::Win), 9);
}

