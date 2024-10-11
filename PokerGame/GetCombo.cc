#include "GetCombo.h"

#include <set>


std::unordered_map<int, int> getRankFrequency(const std::vector<Card>& hand)
{
    std::unordered_map<int, int> rankCount;
    for (Card card : hand) {
        rankCount[card.getRank()]++;
    }
    return rankCount;
}

std::unordered_map<int, int> getSuitFrequency(const std::vector<Card>& hand)
{
    std::unordered_map<int, int> suitCount;
    for (Card card : hand) {
        suitCount[card.getSuit()]++;
    }
    return suitCount;
}
void resetWinHand(std::vector<Card>& winHand)
{
    winHand.clear();
}
Player randomPlayer(Player player1, Player player2)
{
     if(rand() % 2 == 1)
     {
         return player1;
     }
    return player2;
}
Card::rank lowestCard(const std::vector<Card>& cards)
{
    Card lowestCard = cards[0];
    for (Card card : cards) {
        if(card.getRank() < lowestCard.getRank())
        {
            lowestCard = card;
        }
    }
    return lowestCard.getRank();
}
Card::rank highCard(const std::vector<Card>& cards)
{
    Card highestCard = cards[0];
    for (Card card : cards) {
        if(card.getRank() > highestCard.getRank())
        {
            highestCard = card;
            
        }
    }
    return highestCard.getRank();
}
void highCard(const std::vector<Card>& cards, std::vector<Card>& winHand)
{
    Card highestCard = cards[0];
    for (Card card : cards) {
        if(card.getRank() > highestCard.getRank())
        {
            highestCard = card;
        }
    }
    winHand.clear();
    winHand.emplace_back(highestCard);
}
bool isFlush(const std::vector<Card>& cards, std::vector<Card>& winHand)
{
    for (auto frequency : getSuitFrequency(cards))
    {
        if (frequency.second >= 5)
        {
            Card::suit flushSuit = static_cast<Card::suit>(frequency.first);
            std::vector<Card> tempWinHand;
            for (Card card : cards)
            {
                if (card.getSuit() == flushSuit)
                {
                    tempWinHand.emplace_back(card);
                }
            }
            winHand = tempWinHand;
            return true;
        }
    }
    return false;
}


bool isStraight(const std::vector<Card>& cards, std::vector<Card>& winHand)
{
    std::set<int> ranks;
    for (Card card : cards) {
        ranks.insert(card.getRank());
    }
    if (ranks.size() < 5) {
        return false;
    }
    std::vector<int> sortedRanks(ranks.begin(), ranks.end());
    for (int i = 0; i <= sortedRanks.size() - 5; ++i)
    {
        if (sortedRanks[i + 4] - sortedRanks[i] == 4) {
            std::vector<Card> tempWinHand;
            for (Card card : cards) {
                if (card.getRank() >= sortedRanks[i] && card.getRank() <= sortedRanks[i + 4]) {
                    tempWinHand.emplace_back(card);
                }
            }
            winHand = tempWinHand;
            return true;
        }
    }
    return false;
}

bool isPair(const std::vector<Card>& cards, std::vector<Card>& winHand)
{
    for (auto frequency : getRankFrequency(cards))
    {
        if (frequency.second == 2)
        {
            std::vector<Card> tempWinHand;
            for (Card card : cards) {
                if (card.getRank() == frequency.first) {
                    tempWinHand.emplace_back(card);
                }
            }
            winHand = tempWinHand;
            return true;
        }
    }
    return false;
}

bool isTwoPair(const std::vector<Card>& cards, std::vector<Card>& winHand)
{
    int twoPair = 0;
    std::vector<Card> tempWinHand;
    for (auto frequency : getRankFrequency(cards))
    {
        if (frequency.second == 2)
        {
            for (Card card : cards) {
                if (card.getRank() == frequency.first) {
                    tempWinHand.emplace_back(card);
                }
            }
            twoPair++;
        }
    }
    if (twoPair >= 2) {
        winHand = tempWinHand;
        return true;
    }
    return false;
}

bool isThreeOfAKind(const std::vector<Card>& cards, std::vector<Card>& winHand)
{
    std::vector<int> threeOfAKindRanks;
    for (auto frequency : getRankFrequency(cards))
    {
        if (frequency.second == 3)
        {
            threeOfAKindRanks.emplace_back(frequency.first);
        }
    }
    if (!threeOfAKindRanks.empty())
    {
        std::sort(threeOfAKindRanks.begin(), threeOfAKindRanks.end(), std::greater<int>());
        
        int highestRank = threeOfAKindRanks[0];
        std::vector<Card> tempWinHand;
        for (Card card : cards)
        {
            if (card.getRank() == highestRank)
            {
                tempWinHand.emplace_back(card);
            }
        }
        winHand = tempWinHand;
        return true;
    }
    return false;
}



bool isFullHouse(const std::vector<Card>& cards, std::vector<Card>& winHand)
{
    std::vector<int> threeOfAKindRanks;
    std::vector<int> pairRanks;
    std::vector<Card> tempWinHand;
    
    for (auto frequency : getRankFrequency(cards))
    {
        if (frequency.second == 3)
        {
            threeOfAKindRanks.emplace_back(frequency.first);
        }
        else if (frequency.second == 2)
        {
            pairRanks.emplace_back(frequency.first);
        }
    }

    if (!threeOfAKindRanks.empty())
    {
        int highestThreeOfAKind = threeOfAKindRanks[0];
        
        for (Card card : cards)
        {
            if (card.getRank() == highestThreeOfAKind)
            {
                tempWinHand.emplace_back(card);
            }
        }
        
        if (!pairRanks.empty() || threeOfAKindRanks.size() >= 2)
        {
            int highestPairRank = !pairRanks.empty() ? pairRanks[0] : threeOfAKindRanks[1];
            
            for (Card card : cards)
            {
                if (card.getRank() == highestPairRank && tempWinHand.size() < 5)
                {
                    tempWinHand.emplace_back(card);
                }
            }

            winHand = tempWinHand;
            return true;
        }
    }

    return false;
}

bool isFourOfAKind(const std::vector<Card>& cards, std::vector<Card>& winHand)
{
    for (auto frequency : getRankFrequency(cards))
    {
        if (frequency.second == 4)
        {
            std::vector<Card> tempWinHand;
            for (Card card : cards)
            {
                if (card.getRank() == frequency.first)
                {
                    tempWinHand.emplace_back(card);
                }
            }
            winHand = tempWinHand;
            return true;
        }
    }
    return false;
}

bool isStraightFlush(const std::vector<Card>& cards, std::vector<Card>& winHand)
{
    std::vector<Card> flushCards;
    if (!isFlush(cards, flushCards)) {
        return false;
    }
    if (isStraight(flushCards, winHand)) {
        return true;
    }
    winHand.clear();
    return false;
}

bool isRoyalFlush(const std::vector<Card>& cards, std::vector<Card>& winHand)
{
    std::set<Card::rank> royalValues = { Card::rank::ten, Card::rank::jack, Card::rank::queen, Card::rank::king, Card::rank::ace };
    std::set<Card::rank> flushValues;
    Card::suit flushSuit;
    std::vector<Card> tempWinHand;
    for (auto card : cards)
    {
        if (flushValues.empty() || card.getSuit() == flushSuit)
        {
            flushSuit = card.getSuit();
            flushValues.insert(card.getRank());
        }
        else
        {
            flushValues.clear();
        }
        if (flushValues.size() >= 5 && std::includes(flushValues.begin(), flushValues.end(), royalValues.begin(), royalValues.end()))
        {
            for (Card::rank royalRank : royalValues)
            {
                for (Card card : cards)
                {
                    if (card.getRank() == royalRank && card.getSuit() == flushSuit)
                    {
                        tempWinHand.emplace_back(card);
                    }
                }
            }
            winHand = tempWinHand;
            return true;
        }
    }
    return false;
}
