#include <iostream>
#include <vector>
#include <exception>

#include <Game.hpp>

#define DEAL_OPT 1
#define STAND_OPT 1
#define HIT_OPT 2
#define QUIT_OPT 9



int main()
{
    /*
    std::vector<Card> test_hand({Card(Suit::Spade, 10), Card(Suit::Club, 13), Card(Suit::Diamond, 10)});
    std::cout << "Score: " << std::endl << Game::score_hand(test_hand) << std::endl;
    */

    std::string input;
    unsigned int option = 0;

    Game* game = Game::instance();
    while(game->get_state() != State::Quit)
    {
        game->print_game_state();
        game->print_options();
        std::cin >> input;
        try
        {
            option = std::stoi(input);
        }
        catch(const std::invalid_argument& e)
        {
            option = 0;
        }
        if(option > 0)
        {
            game->player_option(option);
        }
        else
        {
            std::cout << "Bad input" << std::endl;
        }
    }
    return 0;
}