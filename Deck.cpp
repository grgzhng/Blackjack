#include <ctime>
#include "Deck.h"
#include "Card.h"

Deck::Deck()
: m_top(0)
{
    for (int suit = 1; suit <= 4; suit++) {
        for (int value = 1; value <= 13; value++) {
            m_deck.push_back(Card(value, suit));
        }
    }
}

void Deck::shuffle(int n)
{
    srand(time(NULL));
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() % (n - i);
        auto t = m_deck[i];
        m_deck[i] = m_deck[j];
        m_deck[j] = t;
    }
}

Card Deck::draw() {
    return m_deck[m_top++];
}
