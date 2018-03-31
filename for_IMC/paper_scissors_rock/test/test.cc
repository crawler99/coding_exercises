#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "choice.h"

using namespace std;
using namespace psr;

TEST(PSR, Correctness)
{
    PSRRule rule;
    PSRGame game(rule, 10);

    auto *paper_player = new PSRPaperPlayer("Player_Paper");
    auto *scissors_Player = new PSRScissorsPlayer("Player_Scissors");
    auto *rock_Player = new PSRRockPlayer("Player_Rock");

    game.AddPlayer(paper_player);
    game.AddPlayer(rock_Player);
    game.Play();

    EXPECT_EQ(10, paper_player->GetRstNum(JudgeRst::Win));
    EXPECT_EQ(10, rock_Player->GetRstNum(JudgeRst::Lose));

    game.CleanPlayers();
    game.AddPlayer(scissors_Player);
    game.AddPlayer(rock_Player);
    game.Play();

    EXPECT_EQ(10, scissors_Player->GetRstNum(JudgeRst::Lose));
    EXPECT_EQ(10, rock_Player->GetRstNum(JudgeRst::Win));

    game.AddPlayer(paper_player);
    game.Play();
    EXPECT_EQ(10, paper_player->GetRstNum(JudgeRst::Draw));
    EXPECT_EQ(10, scissors_Player->GetRstNum(JudgeRst::Draw));
    EXPECT_EQ(10, rock_Player->GetRstNum(JudgeRst::Draw));
}

