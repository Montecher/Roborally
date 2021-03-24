#include "Deck.hpp"
#include <cstdlib>

template<typename T>
Deck<T>::Deck() {
    dealtCards = 0;
}

template<typename T>
T& Deck<T>::draw() {
    if(dealtCards == deck.size()) shuffle();
    return deck[dealtCards++];
}

template<typename T>
std::vector<T> Deck<T>::deal(int count) {
    std::vector<T> hand;
    for(int i=0; i<count; i++) hand.push_back(draw());
    return hand;
}

template<typename T>
void Deck<T>::shuffle() {
    dealtCards = 0;
    for(int i=deck.size()-1; i>0; i--) {
        int j = rand() % (i+1);
        std::swap(deck[i], deck[j]);
    }
}


template<typename T>
void Deck<T>::add(T card) {
    deck.push_back(card);
}

template<typename T>
void Deck<T>::add(std::vector<T> cards) {
    for(auto card: cards) deck.push_back(card);
}

template<typename T>
void Deck<T>::add(T card, int count) {
    for(int i=0; i<count; i++) deck.push_back(card);
}

template<typename T>
void Deck<T>::add(std::vector<std::pair<T, int>> cards) {
    for(auto pair: cards) add(pair.first, pair.second);
}
