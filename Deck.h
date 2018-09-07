
#ifndef Deck_h
#define Deck_h

#include <vector>
#include "Card.h"

class Deck {
public:
    Deck();
    void shuffle(int n);
    Card draw();
private:
    std::vector<Card> m_deck;
    int m_top;
};

#endif
