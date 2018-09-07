
#include <iostream>
#include <unistd.h>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Hand.h"

using namespace std;

void startGame() {
    cout << "--------------------" << endl;
    cout << "Welcome to Blackjack" << endl;
    cout << "--------------------" << endl;
}

void endGame() {
    cout << "\nThanks for playing!" << endl;
}

int rounds() {
    cout << "How many rounds would you like to play today? ";
    int rounds;
    cin >> rounds;
    while(cin.fail() || rounds < 0) {
        cout << "Please enter a valid number." << std::endl;
        cout << "How many rounds would you like to play today? ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> rounds;
    }
    switch (rounds) {
        case 0:
            return -1;
        case 1:
            cout << "\nStarting " << rounds << " round of Blackjack" << endl;
            break;
        default:
            cout << "\nStarting " << rounds << " rounds of Blackjack" << endl;
    }
    return rounds;
}

void drawCard(Hand& h, Deck& d) {
    h.addCard(d.draw());
}

void startHands(const Hand p, const DealersHand d) {
    cout << "Your hand is: ";
    p.printHand();
    cout << "The dealer's first card is: ";
    d.printSingle();
}

bool blackjack(const Hand hOne, const Hand hTwo) {
    if (hOne.blackjack()) {
        if (hTwo.blackjack()) {
            cout << "Wow, double blackjack!" << endl;
            cout << "TIE" << endl;
        } else {
            cout << "Blackjack!" << endl;
            cout << "YOU WIN" << endl;
        }
        usleep(1000000);
        return true;
    }
    if (hTwo.blackjack()) {
        cout << "Dealer has a blackjack: ";
        hTwo.printHand();
        cout << "YOU LOSE" << endl;
        usleep(1000000);
        return true;
    }
    return false;
}

// returns whether or not player busted
bool playerTurn(Hand& h, Deck& d) {
    string resp;
    do {
        cout << "Stand or hit? (s/h) " << endl;
        cin >> resp;
        while (resp != "s" && resp != "h") {
            cout << "Invalid response. Please enter either 's' or 'h'." << endl;
            cout << "Stand or hit? (s/h) " << endl;
            cin >> resp;
        }
        if (resp == "s")
            break;
        else {
            h.addCard(d.draw());
            cout << "Your new hand is: ";
            h.printHand();
            if (h.bust()) {
                cout << "You went over 21 - bust!" << endl;
                cout << "YOU LOSE" << endl;
                return true;
            }
        }
    } while (resp == "h");
    return false;
}

bool dealerTurn(DealersHand& h, Deck& d) {
    cout << "The dealer's hand is: ";
    h.printHand();
    while (h.count() < 17) {
        h.addCard(d.draw());
        cout << "The dealer hits. His new hand is: ";
        h.printHand();
    }
    
    // check dealer bust
    if (h.bust()) {
        cout << "Dealer went over 21 - bust!" << endl;
        cout << "YOU WIN" << endl;
        return true;
    }
    return false;
}

const void result(Hand h, DealersHand dh) {
    cout << "Your hand's value is: ";
    cout << h.count();
    cout << "\nThe dealer's hand's value is: ";
    cout << dh.count();
    cout << "\n";
    
    if (h.count() > dh.count()) {
        cout << "YOU WIN" << endl;
    } else if (h.count() < dh.count()) {
        cout << "YOU LOSE" << endl;
    } else {
        cout << "TIE" << endl;
    }
}

int main() {
    startGame();
    
    int numRounds, totRounds;
    totRounds = numRounds = rounds();
    
    while (numRounds--) {
        cout << "\nRound " << totRounds - numRounds << endl;
        
        Deck deck;
        deck.shuffle(52);
        
        Hand pHand;
        DealersHand dHand;
        for (int i = 0; i < 2; i++) {
            drawCard(pHand, deck);
            drawCard(dHand, deck);
        }
        startHands(pHand, dHand);
        
        // check for blackjacks
        if (blackjack(pHand, dHand))
            continue;
        
        // player's turn
        // if player busted, next round
        if (playerTurn(pHand, deck)) {
            continue;
        }
        
        // dealer's turn
        // if dealer busted, next round
        if (dealerTurn(dHand, deck)) {
            continue;
        }
        
        // get result
        result(pHand, dHand);
    }
    endGame();
}
