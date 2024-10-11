#pragma once
#include <vector>
#include "Card.h"

class Hand
{
private:
   std::vector<Card> hand;
public:
   std::vector<Card> getHand();
   void addToHand(Card card);
   void CreatePlayerHand(std::vector<Card>& deck);
   int getSize(){return hand.size();}
   Hand() : hand() {}
   Hand(std::vector<Card>& cards)
   {
      CreatePlayerHand(cards);
   }
};
