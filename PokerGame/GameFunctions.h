#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>
#include <__msvc_filebuf.hpp>
#include "Card.h"
#include "Hand.h"
#include "Player.h"

void initializeGlobalCards( std::vector<Card>& globalCards, std::vector<Card>& deck);
void addToGlobalCards( std::vector<Card>& globalCards, std::vector<Card>& deck);
Player whoWinsBetween(Player& player1, Player& player2, std::vector<Card> globalCard);
Player whoWins(std::vector<Player>& players, std::vector<Card> globalCards);
bool isNumber();
bool action(int choice, Player& player, int& bank, int& maxBet, std::vector<Card> globalCards);
int raiseRandomNumber(int max);
bool stopGame(std::vector<Player> players);
bool checkBet(std::vector<Player> players, int maxBet);
std::vector<Player> getPlayersNeedingToFollow(const std::vector<Player>& players, int maxBet);
bool canContinueGame(const std::vector<Player>& players);