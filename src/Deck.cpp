#include <Deck.hpp>
#include <algorithm>

Deck::Deck(const unsigned int& deck_size) : _deck_size(deck_size)
{
    for(unsigned int i = 0; i < deck_size; i++)
    {
        for(unsigned int r = MINRANK; r <= MAXRANK; r++)
        {
            _deck.push_back(Card(Suit::Spade, r));
            _deck.push_back(Card(Suit::Heart, r));
            _deck.push_back(Card(Suit::Club, r));
            _deck.push_back(Card(Suit::Diamond, r));
        }
    }
}


Card Deck::deal()
{
    Card c = _deck.front();
    _deck.pop_front();
    return c;
}
const unsigned int Deck::remaining_cards() const
{
    return _deck.size();
}

void Deck::shuffle()
{
    std::random_shuffle(_deck.begin(), _deck.end());
}

void Deck::clear()
{
    _deck.clear();
}

void Deck::add_to_back_of_deck(const Card& c)
{
    _deck.push_back(c);
}