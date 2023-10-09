#include "Pack.hpp"
#include <vector>

using namespace std;
Pack::Pack(){
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