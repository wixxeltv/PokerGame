#pragma once
#include "Card.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
class Deck
{
private:
    std::vector<Card> deck;
    void initializeDeck();
    void shuffleDeck();
public:
    void resetDeck();
     std::vector<Card>& getDeck(){return deck;}
    Card getCard(Card::rank r, Card::suit s);
    Deck()
    {
        initializeDeck();
        shuffleDeck();
    }
};
