#include "Player.hpp"
#include <string>
#include <vector>
#include <cassert>
#include <array>
#include <algorithm>

class SimplePlayer: public Player{
  private:
    std::string name;
    std::vector<Card> hand;
  public:
    SimplePlayer(std::string name):
    name(name){};

    //EFFECTS returns player's name
    const std::string & get_name() const override{
      return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override{
      assert(hand.size() <= MAX_HAND_SIZE);
      hand.push_back(c);
      std::sort(hand.begin(), hand.end());
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
      if (round == 1){
        for (int i = 0; i < hand.size(); ++i){
          if (hand.at(i).get_suit() == upcard.get_suit()&&
          hand.at(i).is_face_or_ace()){
            ++f_or_aT;
          }
        }
        if (f_or_aT > 1){
          order_up_suit = upcard.get_suit();
          return true;
        }
        else{
          return false;
        }
      }
      else{
        for (int i = 0; i < hand.size(); ++i){
          if (Suit_next(hand.at(i).get_suit()) == upcard.get_suit()){
            samecolor = true;
            ou_suit = hand.at(i).get_suit();
          }
        }
        
        if(samecolor){
          order_up_suit = ou_suit;//not hitting
          return true;
        }
        else if (!samecolor){
          order_up_suit = upcard.get_suit();
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
      int lowest_index = 0;
      for (int i = 0; i < hand.size(); ++i)
      {
        if (Card_less(hand.at(i), lowest,upcard.get_suit()))
        {
          lowest = hand.at(i);
          lowest_index = i;
        }
      }
      hand.erase(hand.begin() + lowest_index);
      hand.push_back(upcard);
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) override{
      assert(hand.size() >= 1);
      Card largest = hand.at(0);
      Card largest_allt = hand.at(0);
      int trump_counter = 0;
      int index1 = 0;
      int index2 = 0;
      for (int i = 0; i < hand.size(); ++i){
        if (hand.at(i).get_suit() == trump){
          ++trump_counter;
        }
        if (largest < hand.at(i) && hand.at(i).get_suit() != trump)
        {
          largest = hand.at(i);
          index1 = i;
        }
        if (largest_allt < hand.at(i))
        {
          largest_allt = hand.at(i);
          index2 = i;
        }
      }

      if (trump_counter == hand.size()){
        hand.erase(hand.begin()+index2);
        return largest_allt;
      }
      else{
        hand.erase(hand.begin()+index1);
        return largest;
      }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override{
      assert(hand.size() >= 1);
      int del_index = 0;
      bool follow_suit = false;
      Card follow = hand.at(0);

      for (int i = 0; i < hand.size(); ++i){
        if (hand.at(i).get_suit() == led_card.get_suit() &&
        hand.at(i) > led_card)
        {
          follow_suit = true;
          if (hand.at(i) > follow)
          {
            follow = hand.at(i);
            del_index = i;
          }
        }
      }
      if (follow_suit){
        hand.erase(hand.begin()+del_index);
        return follow;
      }
      else{
        for (int i = 0; i < hand.size(); ++i)
        {
          if (Card_less(hand.at(i), follow, trump))
          {
            follow = hand.at(i);
            del_index = i;
          }
        }
        hand.erase(hand.begin() + del_index);
        return follow;
      }
    }
    
    ~SimplePlayer() override{};
};

class HumanPlayer: public Player{
  private:
    std::string name;
    std::vector<Card> hand;
    void print_hand() const {
      for (size_t i=0; i < hand.size(); ++i)
        std::cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
    }
  public:
    HumanPlayer(std::string name):
    name(name){};
  
    const std::string & get_name() const override{
      return name;
    }

    void add_card(const Card &c) override{
      assert(hand.size() <= MAX_HAND_SIZE);
      hand.push_back(c);
      std::sort(hand.begin(), hand.end());
    }
  
    bool make_trump(const Card &upcard, bool is_dealer,
    int round, Suit &order_up_suit) const override{
      print_hand();
      std::string decision;
      std::cout << "Human player " << name << 
      ", please enter a suit, or \"pass\":\n";
      std::cin >> decision;

      if (decision != "pass"){
        order_up_suit = string_to_suit(decision);
        return true;
      }
      else{
        return false;
      }
    }

    void add_and_discard(const Card &upcard) override{
      print_hand();
      int card_num;
      std::cout << "Discard upcard: [-1]\n";
      std::cout << "Human player " << name << ", please select a card to discard:\n";
      std::cin >> card_num;
      if (card_num >= 0)
      {
        hand.erase(hand.begin() + card_num);
      }
    }

    Card lead_card(Suit trump) override{
      print_hand();
      int card;
      Card cardin;
      std::cout << "Human player " << name << ", please select a card:\n";
      std::cin >> card;
      cardin = hand.at(card);
      hand.erase(hand.begin() + card);
      return cardin;
    };

    Card play_card(const Card &led_card, Suit trump) override{
      return lead_card(trump);
    }
  
    ~HumanPlayer() override{};
};

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

std::ostream & operator<<(std::ostream &os, const Player &p){
  return os << p.get_name();
}