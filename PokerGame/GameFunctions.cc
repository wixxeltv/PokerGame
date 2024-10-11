#include "GameFunctions.h"

#include "GetCombo.h"
void initializeGlobalCards( std::vector<Card>& globalCards, std::vector<Card>& deck)
{
    globalCards.clear();
    for (int i = 0; i < 3; ++i)
    {
        globalCards.emplace_back(deck.back());
        deck.pop_back();
    }
}
int raiseRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}
void addToGlobalCards( std::vector<Card>& globalCards, std::vector<Card>& deck)
{
    globalCards.emplace_back(deck.back());
    deck.pop_back();
}

Player whoWins(std::vector<Player>& players, std::vector<Card> globalCards)
{
    Player winner = players[0];
    for (auto& player : players)
    {
        
        std::cout << "\n" << player.getName() << "\n--------------------\nYour combo : ";
        std::vector<Card> playerHandCopy = player.playerHand.getHand();
        std::vector<Card> fullHand = globalCards; 
        fullHand.insert(fullHand.end(), playerHandCopy.begin(), playerHandCopy.end());
        player.getCombo(fullHand);
        if(player.getTheCombo() > winner.getTheCombo())
        {
            winner = player;
        }
        else if (player.getTheCombo() == winner.getTheCombo())
        {
           winner = whoWinsBetween(winner, player, globalCards);
        }
        std::cout << "With thoses cards : \n";
        for (auto card : player.getWinCards())
        {
            std::cout << card.toStringSuit() << " " << card.toStringRank() << "\n";
        }
        std::cout << "--------------------\n";
    }
    
    return winner;
}
Player whoWinsBetween(Player& player1, Player& player2, std::vector<Card> globalCards) 
{

    std::vector<Card> player1Hand = player1.playerHand.getHand();
    std::vector<Card> fullHand1 = globalCards; 
    fullHand1.insert(fullHand1.end(), player1Hand.begin(), player1Hand.end());
    
    std::vector<Card> player2Hand = player2.playerHand.getHand();
    std::vector<Card> fullHand2 = globalCards;
    
    fullHand2.insert(fullHand2.end(), player2Hand.begin(), player2Hand.end());
    auto sortDescending = []( Card& a,  Card& b) {
        return a.getRank() > b.getRank();
    };
    std::sort(fullHand1.begin(), fullHand1.end(), sortDescending);
    std::sort(fullHand2.begin(), fullHand2.end(), sortDescending);
    for (size_t i = 0; i < std::min(fullHand1.size(), fullHand2.size()); ++i) 
    {
        if (fullHand1[i].getRank() > fullHand2[i].getRank()) 
        {
            return player1;
        } 
        if (fullHand1[i].getRank() < fullHand2[i].getRank()) 
        {
            return player2;
        }
    }
    Player noWinner;
    return noWinner;
}

bool isNumber()
{
    if(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }
        return false;
}
//Check{1}\n Raise{2} \n Fold{1}\n Show hand{4}
bool action(int choice, Player& player, int& bank, int& maxBet, std::vector<Card> globalCards)
{

    if(!player._isPlayer)
    {
        choice = rand() % 3 + 1;
    }
    switch (choice)
    {
        case 1:
            if(player.getBet() < maxBet)
            {
                player.follow(bank,maxBet);
            }
            else
            {
                std::cout << player.getName() <<" checked\n" ;
            }
                return false;
        case 2:
            if(!player._isPlayer && maxBet >= player.getMoney() )
            {
                return true;
            }
            if(player.getMoney() <= 0)
            {
                std::cout << "You can't raise. You don't have money\n";
                return true;
            }
            if(player._isPlayer)
            {
                
                int raise = 0;
                bool error;
                do
                {
                    std::cout << "The max bet is " << maxBet << " and you have " << player.getMoney() << "\n";
                    std::cout << "How much do you want to raise ?\n";
                    std::cin >> raise;
                    if(isNumber() || (raise < 1 || raise > player.getMoney()))
                    {
                        std::cout << "Invalid input\n";
                        error = true;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else error = false;
                }
                while (error);
                return player.raise(raise, bank, maxBet);
            }
            player.raise(raiseRandomNumber(1, player.getMoney() - maxBet), bank, maxBet);
            return false;
        
        case 3:
            if(!player._isPlayer)
            {
                if(player.getBet() >= maxBet)
                {
                    return true;
                }
            }
            std::cout << player.getName() << " fold\n";
            player.isActive = false;
            return false;
            
        case 4:
            std::vector<Card> playerHandCopy = player.playerHand.getHand();
            std::vector<Card> fullHand = globalCards; 
            fullHand.insert(fullHand.end(), playerHandCopy.begin(), playerHandCopy.end());
            std::cout << "--------------------\nYour combo : ";
            player.getCombo(fullHand);
            std::cout << "Your combo card(s) : \n";
            for (auto card : player.getWinCards())
            {
                std::cout << card.toStringSuit() << " " << card.toStringRank() << "\n";
            }
            std::cout << "--------------------\n";
            return true;
            
        
    }
}
bool stopGame(std::vector<Player> players)
{
    int activePlayers = 0;
    for (auto player : players)
    {
        if(player.isActive)
        {
            activePlayers++;
        }
    }
    return activePlayers <= 1;
}

bool checkBet(const std::vector<Player> players, int maxBet)
{
    for (auto player : players)
    {
        if(player.getBet() < maxBet && player.isActive)
        {
           
            return true;
        }
    }
    return false;
}
std::vector<Player> getPlayersNeedingToFollow(const std::vector<Player>& players, int maxBet) {
    std::vector<Player> playersNeedingToFollow;

    for (auto player : players) {
        if (player.isActive && player.getBet() < maxBet) {
            playersNeedingToFollow.emplace_back(player);
        }
    }

    return playersNeedingToFollow;
}