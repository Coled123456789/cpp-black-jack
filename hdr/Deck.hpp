#pragma once
#include <deque>
#include <sstream>
#define MINRANK 1
#define MAXRANK 13
enum Suit {Spade, Heart, Club, Diamond}; 

class Card 
{
    private:
        bool _faceup = true;
    public:
        Suit suit;
        int rank; /* 1 = Ace, 11 = jack, 12 = queen, 13 =  king*/
        Card(Suit s, int r) : Card(s, r, false) {}
        Card(Suit s, int r, bool faceup) : suit(s), rank(r), _faceup(faceup) {}

        const std::string str() const
        {
            if(!_faceup)
            {
                return "DOWN";
            }
            std::stringstream ss;
            switch(suit)
            {
                case Suit::Spade:
                    //ss << "Spade";
                    ss << "Sp";
                    break;
                case Suit::Heart:
                    //ss << "Heart";
                    ss << "He";
                    break;
                case Suit::Club:
                    //ss << "Club";
                    ss << "Cl";
                    break;
                case Suit::Diamond:
                    //ss << "Diamond";
                    ss << "Di";
                    break;
            }
            ss << "-";
            switch(rank)
            {
                case 1:
                    ss << "A";
                    break;
                case 10:
                    ss << "D";
                    break;
                case 11:
                    ss << "J";
                    break;
                case 12:
                    ss << "Q";
                    break;
                case 13:
                    ss << "K";
                    break;
                default:
                    ss << rank;
            }
            return ss.str();
        }

        Card& flip()
        {
            _faceup = !_faceup;
            return *this;
        }
};


class Deck
{
    private:
        unsigned int _deck_size;
        std::deque<Card> _deck;
    public :
        Deck() : Deck(1) {};
        Deck(const unsigned int& deck_size);
        void shuffle();
        Card deal();
        void add_to_back_of_deck(const Card& c);
        const unsigned int remaining_cards() const;
        void clear();
};