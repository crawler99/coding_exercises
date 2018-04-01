#ifndef _FOR_IMC_PAPER_SCISSORS_ROCK_PLAYER_H_
#define _FOR_IMC_PAPER_SCISSORS_ROCK_PLAYER_H_

#include <rule.h>
#include <map>
#include <iostream>

/** This is the abstraction of a player in a Paper-Scissors-Rock-like game.
 *  His/her only dependency is to make a particular 'choice', hence a template parameter.
 */
template <typename ChoiceT>
class Player
{
    public:
        Player(const std::string &name) : _name(name)
        {
        }

        Player(const Player&) = delete;
        Player(Player&&) = delete;
        Player& operator= (const Player&) = delete;
        Player& operator= (Player&&) = delete;
        ~Player() = default;

        const std::string& GetName()
        {
            return _name;
        }

        /** Virtual function, makeing the next choice. */
        virtual ChoiceT GetChoice() = 0;

        /** Taking necessary action after each round.
         *  @my_choice the player's choice in the last round.
         *  @judgement result of the last round for the player.
         *  @observation choices made by all players in the last round.
         */
        void OnJudgement(ChoiceT my_choice, Judgement judgement, std::map<ChoiceT, uint32_t> &observation)
        {
            ++_results[judgement];
            UpdateStrategy(my_choice, judgement, observation);
        }

        /** Adjust playing strategy after each round. Can be overwritten by concrete players.
         *  @my_choice the player's choice in the last round.
         *  @judgement result of the last round for the player.
         *  @observation choices made by all players in the last round.
         */
        virtual void UpdateStrategy(ChoiceT my_choice, Judgement judgement, std::map<ChoiceT, uint32_t> &observation)
        {
        }

        uint32_t GetResultNum(Judgement judgement)
        {
            return _results[judgement];
        }

        /** Provide a chance to quit the game. Currently the game will call this function on each player in every round,
         *  and stop when there are at least one player want to quit.
         */
        virtual bool DecideToQuit()
        {
            return false; // Default to play forever if the game doesn't stop.
        }

    private:
        std::string _name;
        std::map<Judgement, uint32_t> _results;
};

#endif
