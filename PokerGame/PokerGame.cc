#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "GameFunctions.h"
#include "Hand.h"
#include "Player.h"

std::vector<Player> players;
std::vector<Card> globalCards;

int bank = 20;
int maxBet = 0;

int main() {
    srand(time(NULL));
    
    Deck deck;

    std::cout << "Poker? Let's play.\n";
    std::string name;
    while (true) {
        std::cout << "What's your name?\n";
        std::cin >> name;
        if (name.length() < 3) {
            std::cout << "Invalid input. Minimum 3 characters and no spaces.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else break;
    }

    players.emplace_back(Player(name, deck.getDeck(), true));
    
    for (int i = 1; i <= 3; i++) {
        players.emplace_back(Player("Bot " + std::to_string(i), deck.getDeck(), false));
    }

    // Début de la boucle de jeu
    while (true) {
        bool gameStop = false;
        bool hasToFollow = false;
        int previousBet = 0;
        
        for (int j = 1; j <= 4; j++) {
            if (!hasToFollow) {
                std::cout << "-----Round " << j << "-----\n";
                std::cout << "Bank money: " << bank << std::endl;
            }

            for (auto& player : players) {
                if (player.isActive) {
                    system("pause");
                    std::cout << "\n------ " << player.getName() << " is playing ------\n";
                    std::cout << player.getName() << " money: " << player.getMoney() << std::endl;

                    bool notEverythingFine = true;
                    do {
                        int choice = 0;
                        if (player._isPlayer) {
                            std::cout << "Your hand:\n";
                            for (Card& card : player.playerHand.getHand()) {
                                std::cout << card.toStringSuit() << " " << card.toStringRank() << "\n";
                            }

                            bool errorInput;
                            do {
                                std::cout << "Do you want to:\n";
                                player.getBet() < maxBet ? std::cout << " Follow{1}\n" : std::cout << " Check{1}\n";
                                std::cout << " Raise{2}\n Fold{3}\n Show Combo{4}\n";
                                std::cin >> choice;
                                if (isNumber() || (choice < 1 || choice > 4)) {
                                    std::cout << "Invalid input\n";
                                    errorInput = true;
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                } else {
                                    errorInput = false;
                                }
                            } while (errorInput);
                        }
                        notEverythingFine = action(choice, player, bank, maxBet, globalCards);
                    } while (notEverythingFine);
                }
                if (!checkBet(players, maxBet) && player.getBet() != previousBet && player.isActive) {
                    std::cout << "All players are up to date. Moving to the next round.\n";
                    hasToFollow = false;
                    previousBet = maxBet;
                    break;
                }

                if (stopGame(players)) {
                    gameStop = true;
                    break;
                }
            }

            if (gameStop) { break; }

            if (checkBet(players, maxBet)) {
                hasToFollow = true;
                j--;
                continue;
            }

            hasToFollow = false;
            j == 1 ? initializeGlobalCards(globalCards, deck.getDeck()) : addToGlobalCards(globalCards, deck.getDeck());
        }
        
        // Logique de fin de jeu
        std::cout << "\n--------The game is finished--------\n\n";

        std::vector<Player> potentialWinners;
        Player winner;

        for (auto& player : players) {
            if (player.isActive) {
                potentialWinners.emplace_back(player);
            }
        }
        if (potentialWinners.size() == 1) {
            winner = potentialWinners.front();
        } else {
            winner = whoWins(potentialWinners, globalCards);
        }

        std::cout << "The winner for this game ISSSSSSSSSSSSSSSSSS " << winner.getName() << std::endl;
        if (winner.getName() == "no one") {
            std::cout << "It's a tie! Sooooo I'll take all money mouhahahahhaha." << std::endl;
        } else {
            std::cout << bank << " has been added to your wallet.";
            winner.addMoney(bank);
            std::cout << "Now you have " << winner.getMoney() << " you're rich!!.\nNot for too long...\n";
        }

        bank = 0;
        break;
    }
    return 0;
}