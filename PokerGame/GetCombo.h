#pragma once
#include <algorithm>
#include <set>
#include <unordered_map>
#include "Card.h"
#include "Player.h"
#include "cstdbool"
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
Player randomPlayer(Player player1, Player player2);

std::unordered_map<int, int> getRankFrequency(const std::vector<Card>& hand);

std::unordered_map<int, int> getSuitFrequency(const std::vector<Card>& hand);

Card::rank highCard(const std::vector<Card>& cards);
Card::rank lowestCard(const std::vector<Card>& cards);
void highCard(const std::vector<Card>& cards, std::vector<Card>& winHand);
bool isFlush(const std::vector<Card>& cards, std::vector<Card>& winHand);
bool isStraight(const std::vector<Card>& cards, std::vector<Card>& winHand);
bool isPair(const std::vector<Card>& cards, std::vector<Card>& winHand);
bool isTwoPair(const std::vector<Card>& cards, std::vector<Card>& winHand);
bool isThreeOfAKind(const std::vector<Card>& cards, std::vector<Card>& winHand);
bool isFullHouse(const std::vector<Card>& cards, std::vector<Card>& winHand);
bool isFourOfAKind(const std::vector<Card>& cards, std::vector<Card>& winHand);
bool isStraightFlush(const std::vector<Card>& cards, std::vector<Card>& winHand);
bool isRoyalFlush(const std::vector<Card>& cards, std::vector<Card>& winHand);