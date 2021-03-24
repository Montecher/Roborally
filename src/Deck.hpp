#ifndef __DECK_H
#define __DECK_H

#include <vector>

template<typename T>
class Deck {
private:
    std::vector<T> deck;
    int dealtCards;

public:
    Deck();

    T& draw();
    std::vector<T> deal(int count);
    void shuffle();

    void add(T card);
    void add(std::vector<T> cards);
    void add(T card, int count);
    void add(std::vector<std::pair<T, int>> cards);
};

#include "Deck.cpp"

#endif

