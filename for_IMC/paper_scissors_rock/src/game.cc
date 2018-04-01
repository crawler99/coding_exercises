#include "game.h"

namespace psr {

std::string GetChoiceName(const Choice &choice)
{
    switch (choice)
    {
        case Choice::Paper: return "Paper";
        case Choice::Scissors: return "Scissors";
        case Choice::Rock: return "Rock";
        default: return "(Unknown)";
    }
}

void Game::PrintPlayerChoices(const std::map<Choice, std::set<Player*>> &choices) const
{
    for (auto &pair : choices)
    {
        for (const auto &p : pair.second)
        {
            if (p)
            {
                std::cout << p->GetName() << " => " << GetChoiceName(pair.first) << std::endl;
            }
        }
    }
}

}
