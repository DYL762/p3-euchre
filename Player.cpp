#include "Player.hpp"
#include <string>
#include <vector>
#include <cassert>
#include <array>

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  else if(strategy == "Human"){
    return new HumanPlayer(name);
  }
  // Repeat for each other type of Player
  
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

class SimplePlayer: public Player{
  private:
    std::string name;
    std::vector<Card> hand;
  public:
    SimplePlayer(std::string name):
    name(name), hand_size(0){};

  //EFFECTS returns player's name
  const std::string & get_name() const override{
    return name;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override{
    assert(hand.size() <= MAX_HAND_SIZE);
    hand.push_back(c);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
  int round, Suit &order_up_suit) const override{
    assert(round==1||round==2);
    Suit ou_suit;
    bool samecolor = false;
    int f_or_aT = 0;
    for (int i = 0; i < hand.size(); ++i){
      if (hand.at(i).get_suit() == upcard.get_suit()&&
      hand.at(i).is_face_or_ace()){
        ++f_or_aT;
        if (Suit_next(hand.at(i).get_suit()) == upcard.get_suit()){
        samecolor = true;
        ou_suit = hand.at(i).get_suit();
        }
      }
    }
    if (round == 1){
      if (f_or_aT >= 1){
        order_up_suit = upcard.get_suit();
        return true;
      }
      else{
        return false;
      }
    }
    else{
      if (f_or_aT >= 1){
        if(samecolor){
          order_up_suit = ou_suit;
        }
        else{
          order_up_suit = upcard.get_suit();
        }
        return true;
      }
      else if(is_dealer){
        order_up_suit = upcard.get_suit();
        return true;
      }
      else{
        return false;
      }
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override{
    assert(hand.size() >= 1);
    Card lowest = hand.at(0);
    int lowest_index;
    for (int i = 0; i < hand.size(); ++i)
    {
      if (Card_less(hand.at(i), lowest,upcard.get_suit()))
      {
        lowest_index = i;
        lowest = hand.at(i);
      }
    }
    hand.erase(hand.begin() + lowest_index);
    hand.push_back(lowest);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(Suit trump) override{
    assert(hand.size() >= 1);
    Card largest = hand.at(0);
    for (int i = 0; i < hand.size(); ++i){
      if (Card_less(largest, hand.at(i), trump))
      {
        largest = hand.at(i);
      }
    }
    return largest;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, Suit trump) override{
    assert(hand.size() >= 1);
    
  }
};