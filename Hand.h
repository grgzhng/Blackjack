
#ifndef Hand_h
#define Hand_h

#include <vector>
#include "Card.h"
#include "Deck.h"

class Hand
{
public:
    void addCard(Card card);
    void printHand() const;
    int count() const;
    bool bust() const;
    bool blackjack() const;
protected:
    std::vector<Card> m_hand;
};

class DealersHand: public Hand
{
public:
    void printSingle() const;
};

#endif
