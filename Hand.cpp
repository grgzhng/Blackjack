
#include <iostream>
#include "Hand.h"

using namespace std;

void Hand::addCard(Card card) {
    m_hand.push_back(card);
}

void Hand::printHand() const {
    for (int i = 0; i < m_hand.size(); i++) {
        m_hand[i].printCard();
    }
    cout << "\n";
}

int Hand::count() const {
    int aces = 0;
    int tot = 0;
    for (int i = 0; i < m_hand.size(); i++) {
        int val = m_hand[i].getValue();
        tot += val;
        if (val == 1)
            aces++;
    }
    while (aces > 0 && tot < 12) {
        aces--;
        tot += 10;
    }
    return tot;
}

bool Hand::bust() const {
    return count() > 21;
}

bool Hand::blackjack() const {
    return m_hand.size() == 2 && count() == 21;
}

void DealersHand::printSingle() const {
    if (m_hand.empty()) return;
    m_hand[0].printCard();
    cout << "\n";
}
