#include <iostream>
#include "Player.hpp"
#include "Card.hpp"
#include "Pack.hpp"
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
using namespace std;

class Game {
 public:
  Game(Pack pack_in, bool shuffle_in, vector<Player*> players_in, int points_in){
    pack_in = pack;
    shuffletf = shuffle_in;
    points = points_in;
    for (int i = 0; i < players_in.size(); ++i){
      players.at(i) = players_in.at(i);    
    }
  };

  void play(){

  };

  private:
    vector<Player*> players;
    Pack pack;
    int points;
    int pointst02;
    int points13;
    int round;
    int curr_lead;
    string trump_side;
    bool shuffletf;
    Suit trump;
    void shuffle(){
      pack.shuffle();
    };
    void deal(Pack &pack, vector<Player*> players){
      cout << "hand 0" << endl;
      cout << players[0]->get_name() << " deals";
      int amt;
      for (int i = 0; i < 2; ++i)
      {
        for (int j = 0; j < players.size(); ++j)
        {
          if (i == 0){
            if (j == 0||j%2 == 0){
              deal_batch(players[j], pack ,3);
            }
            else{
              deal_batch(players[j], pack, 2);
            }
          }
          else{
            if (j == 0||j%2 == 0){
              deal_batch(players[j], pack, 2);
            }
            else{
              deal_batch(players[j], pack, 3);
            }
          }
        }
      }
    };

    void deal_batch(Player* player, Pack pack, int amt){
      for (int i = 0; i < amt; ++i)
      {
        player->add_card(pack.deal_one());
      }
    }

    void make_trump(vector<Player*> players, int round, Pack &pack){
      Card upcard = pack.deal_one();
      cout << upcard << " turned up" << endl;
      Suit orderup;
      curr_lead = 1;
      for (int i = 1; i < players.size()+1; ++i)
      {
        bool isdealer = false;
        if (players[i]->make_trump(upcard,isdealer, 
        round, orderup)){

          cout << players[i]->get_name() << " orders up "
          << orderup << endl;
          trump_side = set_trump_team(i);
          trump = orderup;
          break;
        }
        else{
          cout << players[i]->get_name() << " passes";
        }
        if (i == players.size()){
          isdealer = true;

          if (players[0]->make_trump(upcard,isdealer, 
          round, orderup)){

            cout << players[i]->get_name() << " orders up "
            << orderup << endl;
            trump_side = set_trump_team(i);
            trump = orderup;
            break;
          }
        }  
      }
    };

    string set_trump_team(int i){
      if(i==0||i==2){
        return "02";
      }
      else{
        return "13";
      }
    }

    void play_hand(vector<Player*> players, Suit trump, int lead){
      Card lead_card = players[lead]->lead_card(trump);
      cout << lead_card << " led by " 
      << players[lead]->get_name();
      int start;
      if (lead == 3){
          start = 0;
      }
      else{
        start = lead+1;
      }
      for (int i = start; i < players.size()-1; ++i)
      {
        if (players[i]->get_name() == 
        players.back()->get_name()){
          if (i < ){
            i = 0;
          }
        }
        
      }
      
      
    };
};

int main(int argc, char **argv) {
  // Read command line args and check for errors
  bool error;
  string pack_filename = argv[1];
  string shuffle = argv[2];
  int points = stoi(argv[3]);
  vector<Player*> players;
  bool shuffletf;

  ifstream fin;
  fin.open(pack_filename);

  if (!fin.is_open()){
    cout << "Error opening " << pack_filename << endl;
  }

  Pack pack(fin);

  if (argc == 12){
    for (int i = 5; i < 12; i+=2){
      string strat = argv[i];
      if (!(strat=="Simple")&&!(strat=="Human")){
        error = true;
        break;
      }
    }
    if (shuffle == "shuffle"){
      shuffletf = true;
    }
    else if (shuffle == "noshuffle"){
      shuffletf =true;
    }
    else{
      error = true;
    }
  }
  else{
    error = true;
  }
  
  if (error){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
    return 1;
  }


  for (int i = 4; i < 11; i+=2)
  {
    string name = argv[i];
    string strat = argv[i+1];
    players.push_back(Player_factory(name, strat));
  }
  

  Game game(pack, shuffletf, players, points);
  game.play();

  for (size_t i = 0; i < players.size(); ++i) {
    delete players[i];
  }
  return 0;
}
