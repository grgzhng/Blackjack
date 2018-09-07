#include <iostream>
#include "Card.h"

using namespace std;

const string values[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const char suits[] = {'C', 'D', 'H', 'S'};

void Card::printCard() const {
    cout << values[m_value - 1] << suits[m_suit - 1] << " ";
}

int Card::getValue() const {
    if (m_value > 10)
        return 10;
    return m_value;
}
