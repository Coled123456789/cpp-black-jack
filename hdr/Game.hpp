#pragma once

#include <vector>

#include <Deck.hpp>
enum State
{
    Start,
    PlayerPlay,
    DealerPlay,
    EndPlay,
    Quit
};

enum Result
{
    InProgress,
    PlayerWin,
    DealerWin,
    Draw
};
class Game
{
    private:
        static Game* _instance;
        State _state;
        Result _result = Result::InProgress;
        static std::string stringify_hand(const std::vector<Card>&);
    protected:
        Game() : Game(1) {};
        Game(const int& deck_size) :_deck(deck_size) { _deck.shuffle(); };
        Deck _deck;
        std::vector<Card> _dealer_hand;
        std::vector<Card> _player_hand;
        unsigned int _player_bet;
        void dealer_play();
        void evaluate_game_result();

    public:
        void print_options() const;
        void player_option(const unsigned int opt);
        void print_game_state() const;
        static Game* instance();
        static uint score_hand(const std::vector<Card>& hand);

        State get_state() const { return _state; };

        // for debugging
        void use_test_deck(unsigned int rank);
        void use_deck(const Deck& d);
};