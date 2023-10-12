#include "Pack.hpp"
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;
Pack::Pack(){
    next = 0;
    Suit current_suit = SPADES;
    Rank current_rank = NINE;
    for (int i = 0; i < PACK_SIZE; ++i)
    {
        Card card(current_rank, current_suit);
        cards.at(i) = card;
        int r = current_rank;
        current_rank = static_cast<Rank>(r+1);
        if ((i+1)%6 == 0)
        {
            int s = current_suit;
            current_suit = static_cast<Suit>(s+1);
            current_rank = NINE;
        }
    }  
};

Pack::Pack(std::istream& pack_input){
    next = 0;
    for (int i = 0; i < PACK_SIZE; ++i)
    {
        Card card;
        pack_input >> card;
        cards.at(i) = card;
    }
}

Card Pack::deal_one(){
    int temp_next = next;
    ++next;
    return cards.at(temp_next);
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){
    const int size = PACK_SIZE/2;
    array<Card, size> first_half;
    array<Card, size> second_half;
    const int shufflenum = 7;
    for (int j = 0; j < shufflenum; ++j)
    {
        int i1 = 0;
        int i2 = 0;
        for (int i = 0; i < PACK_SIZE; ++i)
        {
            if (i < size){
                first_half.at(i1) = cards.at(i);
                ++i1;
            }
            else if(i >= size){
                second_half.at(i2) = cards.at(i);
                ++i2;
            }
        }
        i1 = 0;
        i2 = 0;
        for (int i = 0; i < PACK_SIZE; ++i)
        {
            if (i == 0||i%2 == 0){
                cards.at(i) = second_half.at(i2);
                ++i2;
            }
            else{
                cards.at(i) = first_half.at(i1);
                ++i1;
            }
        }
    }
}

bool Pack::empty() const{
    if (next == PACK_SIZE){
        return true;
    }
    else{
        return false;
    }
}

