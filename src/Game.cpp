#include <Game.hpp>
#include <iostream>

Game* Game::_instance = nullptr;

Game* Game::instance()
{
    if(_instance == nullptr)
    {
        _instance = new Game();
    }
    return _instance;
}

// options must be over 0
#define STAND_OPT 1
#define HIT_OPT 2
#define CONT_OPT 1
#define QUIT_OPT 2
void Game::print_options() const
{
    switch(_state)
    {
        case State::Start:
            std::cout << "Insert bet: ";
            break;
        case State::PlayerPlay:
            std::cout << "Stand: " << STAND_OPT << std::endl;
            std::cout << "Hit: " << HIT_OPT << std::endl;
            break;
        case State::EndPlay:
            std::cout << "Continue: " <<  CONT_OPT << std::endl;
            std::cout << "Quit: " <<  QUIT_OPT << std::endl;
            break;
    }
    
}

void Game::player_option(const unsigned int opt)
{
    switch(_state)
    {
        case State::Start:
            _player_bet = opt;
            _state = State::PlayerPlay;
            _result = Result::InProgress;
            _player_hand.push_back(_deck.deal().flip());
            _dealer_hand.push_back(_deck.deal().flip());

            _player_hand.push_back(_deck.deal().flip());
            _dealer_hand.push_back(_deck.deal());
            break;
        case State::PlayerPlay:
            if(opt == STAND_OPT)
            {
                dealer_play();
                evaluate_game_result();
                _state = State::EndPlay;
            }
            else if(opt == HIT_OPT)
            {
                _player_hand.push_back(_deck.deal().flip());
                if(score_hand(_player_hand) > 21)
                {
                    std::cout << "Busted, dealer wins" << std::endl;
                    _result = Result::DealerWin;
                    _state = State::EndPlay;
                }
            }
            break;
        case State::EndPlay:
            if(opt == CONT_OPT)
            {
                _player_hand.clear();
                _dealer_hand.clear();
                _state = State::Start;
            }
            else if(opt == QUIT_OPT)
            {
                _state = State::Quit;
            }
            break;
    }
}

/**
 * Run dealer moves, then return result 
 */
void Game::dealer_play()
{
    _dealer_hand[1].flip();
    uint dealer_score = score_hand(_dealer_hand);
    while(dealer_score < 17)
    {
        _dealer_hand.push_back(_deck.deal().flip());
        dealer_score = score_hand(_dealer_hand);
    }
    
}

void Game::evaluate_game_result()
{
    std::cout << "Dealer drawing" << std::endl;
    uint player_score = score_hand(_player_hand);
    uint dealer_score = score_hand(_dealer_hand);
    if(dealer_score > 21)
    {
        std::cout << "Dealer busted, player wins" << std::endl;
        _result = Result::PlayerWin;
    } else if(dealer_score > player_score)
    {
        std::cout << "Dealer wins!" << std::endl;
        _result = Result::DealerWin;
    }
    else if(dealer_score < player_score)
    {
        std::cout << "Player wins!" << std::endl;
        _result = Result::PlayerWin;
    }
    else
    {
        std::cout << "Game Tie!" << std::endl;
        _result = Result::Draw;
    }

}

void Game::print_game_state() const
{
    switch(_state)
    {
        case State::Start:
            std::cout << "Starting Game" << std::endl;
            break;
        case State::PlayerPlay:
        case State::EndPlay:
            std::cout << "==========================" << std::endl;
            std::cout << "Player bet: " << _player_bet << std::endl;
            std::cout << "Player hand score: " << Game::score_hand(_player_hand) << std::endl;
            std::cout << Game::stringify_hand(_player_hand) << std::endl;
            std::cout << "Player hand: " << Game::score_hand(_player_hand) << std::endl;
            if(_state == State::EndPlay)
            {
                std::cout << "Dealer hand score: " << Game::score_hand(_dealer_hand) << std::endl;
            }
            std::cout << "Dealer hand:" << std::endl;
            std::cout << Game::stringify_hand(_dealer_hand) << std::endl;
            std::cout << "==========================" << std::endl;
            if(_state == State::EndPlay)
            {
                if(_result == Result::DealerWin)
                {
                    std::cout << "Dealer wins!" << std::endl;
                }
                if(_result == Result::PlayerWin)
                {
                    std::cout << "Player wins!" << std::endl;
                }
                if(_result == Result::Draw)
                {
                    std::cout << "Draw!" << std::endl;
                }
            }
            break;
    }

}

/**
 * 
 */
std::string Game::stringify_hand(const std::vector<Card>& hand)
{
    std::stringstream ss;
    ss << "|";
    for(Card c : hand)
    {
        ss << c.str() << "|";
    }
    return ss.str(); 
}

/**
 * gets the best possible blackjack score
 */
uint Game::score_hand(const std::vector<Card>& hand)
{
    int score = 0;
    int aces = 0;
    for(int i = 0; i < hand.size(); i++)
    {
        if(hand[i].rank == 1)
        {
            score += 11;
            aces++;
        }
        else if(hand[i].rank > 10)
        {
            score += 10;
        }
        else
        {
            score += hand[i].rank;
        }
    }   
    while(score > 21 && aces > 0)
    {
        if(aces > 0)
        {
            score -= 10;
            aces--;
        }
    }

    return score;
}

void Game::use_test_deck(unsigned int rank)
{
    _deck.clear();
    Card c(Suit::Spade, rank);
    for(int i = 0; i < 100; i++)
    {
        _deck.add_to_back_of_deck(c);
    }
}