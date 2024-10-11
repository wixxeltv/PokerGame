#pragma once
#include <string>
#include "Hand.h"

class Player
{
private:
    int _money;
    std::string _name;
    int _bet;
    std::vector<Card> winCards;
        enum combo
        {
            Pair,
            TwoPair,
            ThreeOfAKind,
            Straight,
            FourOfAKind,
            Flush,
            FullHouse,
            StraightFlush,
            RoyalFlush
        };
public:
    void resetPlayer(std::vector<Card>& deck);
    bool isActive;
    std::string getName()
    {return _name;}
    void showHand();
    void showHand(std::vector<Card> cards);
    bool follow(int& bank, int maxBet);
    bool raise(int raise, int& bank, int& maxBet);
    int getBet(){return _bet;}
    void setBet(int changeBet){_bet = changeBet;}
    void addMoney(int money){_money +=money;}
    int getMoney(){return _money;}
    combo getTheCombo(){return _combo;}
    std::vector<Card> getWinCards()
    {
        return winCards;
    }
    void getCombo(std::vector<Card> cards);
    combo _combo;

    Hand playerHand;
    bool _isPlayer;

    Player() : _name("no one"), _money(0), _bet(0), isActive(false), playerHand({}) {}
    Player(std::string name,  std::vector<Card>& cards, bool isPlayer) : playerHand(cards), _name(name), _isPlayer(isPlayer), _money(1000), _bet(0), isActive(true){}
};
