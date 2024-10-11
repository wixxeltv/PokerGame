#pragma once
#include <iostream>
#include <string>

class Card
{

public:
enum suit
{
    diamond,
    heart,
    clubs,
    spades
};
enum rank
{
    two = 2,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace
};
suit getSuit(){ return _suit; }
rank getRank(){ return _rank; }
void setCard(Card card)
{
    _suit = card.getSuit();
    _rank = card.getRank();
}    
Card(rank rank, suit suit) : _rank(rank), _suit(suit){}

std::string toStringSuit() {
    switch (_suit) {
    case diamond: return "Diamond";
    case heart: return "Heart";
    case clubs: return "Clubs";
    case spades: return "Spades";
    }
    std::cout << "Error suit: " << _suit ;

}
std::string toStringRank() {
    switch (_rank) {
    case two: return "Two";
    case three: return "Three";
    case four: return "Four";
    case five: return "Five";
    case six: return "Six";
    case seven: return "Seven";
    case eight: return "Eight";
    case nine: return "Nine";
    case ten: return "Ten";
    case jack: return "Jack";
    case queen: return "Queen";
    case king: return "King";
    case ace: return "Ace";
    }
    std::cout << "Error rank: " << _rank;

}

private:
rank _rank;
suit _suit;

};
