#include "Deck.h"

Card Deck::getCard(Card::rank r, Card::suit s) {
    return Card(r, s);
}

void Deck::shuffleDeck()
{
    std::random_shuffle(deck.begin(), deck.end());
}

void Deck::initializeDeck()
{
    for (int i = Card::suit::diamond; i <= static_cast<int>(Card::suit::spades); i++)
    {
        for (int j = Card::rank::two; j <= static_cast<int>(Card::rank::ace); j++)
        {
            deck.emplace_back(Card(static_cast<Card::rank>(j),static_cast<Card::suit>(i)));
        }
    }
}
void Deck::resetDeck()
{
    deck.clear();
    initializeDeck();
}

