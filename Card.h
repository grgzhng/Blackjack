#ifndef Card_h
#define Card_h

struct Card {
public:
    Card(int value, int suit): m_value(value), m_suit(suit) {}
    void printCard() const;
    int getValue() const;
private:
    int m_value;
    int m_suit;
};

#endif
