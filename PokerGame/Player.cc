#include "Player.h"

#include "Deck.h"
#include "GetCombo.h"

void Player::resetPlayer(std::vector<Card>& deck)
{
   Hand newHand(deck);
   playerHand = newHand;
   if(_money > 0 )
   {
      isActive = true;
   }
   
}
void Player::getCombo(std::vector<Card> cards)
{
   highCard(cards, winCards);
   bool foundSomething = false;
   
   if(isRoyalFlush(cards, winCards))
   {
      _combo = RoyalFlush;
      std::cout << "Royal Flush" << std::endl;
      foundSomething = true;
   }
   else if(isStraightFlush(cards, winCards))
   {
      _combo = StraightFlush;
      std::cout << "Straight Flush" << std::endl;
      foundSomething = true;
   }
   else if(isFourOfAKind(cards, winCards))
   {
      _combo = FourOfAKind;
      std::cout << "Four of a Kind" << std::endl;
      foundSomething = true;
   }
   else if(isFullHouse(cards, winCards))
   {
      _combo = FullHouse;
      std::cout << "Full House" << std::endl;
      foundSomething = true;
   }
   else if(isFlush(cards, winCards))
   {
      _combo = Flush;
      std::cout << "Flush" << std::endl;
      foundSomething = true;
   }
   else if(isStraight(cards, winCards))
   {
      _combo = Straight;
      std::cout << "Straight" << std::endl;
      foundSomething = true;
   }
   else if(isThreeOfAKind(cards, winCards))
   {
      _combo = ThreeOfAKind;
      std::cout << "Three of a Kind" << std::endl;
      foundSomething = true;
   }
   else if(isTwoPair(cards, winCards))
   {
      _combo = TwoPair;
      std::cout << "Two Pair" << std::endl;
      foundSomething = true;
   }
   else if(isPair(cards, winCards))
   {
      _combo = Pair;
      std::cout << "Pair" << std::endl;
      foundSomething = true;
   }

   if(!foundSomething) std::cout << "High card" << std::endl;
}

bool Player::follow(int& bank, int maxBet) {
   int amountToCall = maxBet - _bet;

   if (amountToCall > _money) {
      std::cout << _name << " is forced to go ALLLLL INNNN with " << _money << " (can't cover the full amount).\n";
      bank += _money;
      _bet += _money;
      _money = 0;
      return false;
   }

   _money -= amountToCall;
   _bet += amountToCall;
   bank += amountToCall;

   std::cout << _name << " followed with " << amountToCall << ". Money left: " << _money << "\n";
   return false;
}


bool Player::raise(int raise, int& bank, int& maxBet)
{
   if (_money < maxBet - _bet + raise)
   {
      std::cout << "The max bet is " << maxBet << " and you have " << _money << "\n";
      std::cout << _name << ", you don't have enough money to raise that amount...\n";
      return true;
   }
   
   bank += raise;
   _money -= (raise + (maxBet - _bet));
   _bet += (maxBet - _bet) + raise;
   maxBet += raise;


   std::cout << _name << " added " << raise << " to the bet. The total bet is now " << maxBet << ".\n";
   std::cout << _name << " money is now : " << _money << "\n";

   return false;
}


void Player::showHand()
{
   for (auto card : playerHand.getHand())
   {
      std::cout << card.toStringSuit() << " " << card.toStringRank() << "\n";
   }
   
}

void Player::showHand(std::vector<Card> cards)
{
   for (auto card : cards)
   {
      std::cout << card.toStringSuit() << " " << card.toStringRank() << "\n";
   }
   
}