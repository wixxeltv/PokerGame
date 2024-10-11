#include "Hand.h"

#include "Card.h"
#include "Player.h"

std::vector<Card> Hand::getHand()
{
    return hand;
}

void Hand::CreatePlayerHand(std::vector<Card>& deck)
{
    for (int i = 0; i < 2; i++)
    {
        hand.emplace_back(deck.back());
        deck.pop_back();
    }
}