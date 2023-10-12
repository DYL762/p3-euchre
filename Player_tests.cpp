#include "Player.hpp"
#include "unit_test_framework.hpp"
#include "Card.hpp"

#include <iostream>

using namespace std;

Card nine_spades = Card(NINE,SPADES);
Card ten_spades = Card(TEN,SPADES);
Card jack_spades = Card(JACK,SPADES);
Card queen_spades = Card(QUEEN,SPADES);
Card king_spades = Card(KING, SPADES);
Card ace_spades = Card(ACE,SPADES);
Card nine_clubs = Card(NINE,CLUBS);
Card ten_clubs = Card(TEN,CLUBS);
Card jack_clubs = Card(JACK,CLUBS);
Card queen_clubs = Card(QUEEN,CLUBS);
Card king_clubs = Card(KING,CLUBS);
Card ace_clubs = Card(ACE,CLUBS);
Card nine_hearts = Card(NINE,HEARTS);
Card ten_hearts = Card(TEN,HEARTS);
Card jack_hearts = Card(JACK,HEARTS);
Card queen_hearts = Card(QUEEN,HEARTS);
Card king_hearts = Card(KING,HEARTS);
Card ace_hearts = Card(ACE,HEARTS);
Card nine_diamonds = Card(NINE,DIAMONDS);
Card ten_diamonds = Card(TEN,DIAMONDS);
Card jack_diamonds = Card(JACK,DIAMONDS);
Card queen_diamonds = Card(QUEEN,DIAMONDS);
Card king_diamonds = Card(KING,DIAMONDS);
Card ace_diamonds = Card(ACE,DIAMONDS);
Card two_spades = Card(TWO,SPADES);
Card two_diamonds = Card(TWO,DIAMONDS);

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(LeadCardSimplePlayerScenario) {
    Player *alice = Player_factory("Alice", "Simple");

    // Scenario 1: Leading with Hearts as trump
    alice->add_card(queen_hearts);
    alice->add_card(jack_spades);
    alice->add_card(ace_spades);

    Card test = alice->lead_card(HEARTS);
    ASSERT_EQUAL(test, ace_spades);

    test = alice->lead_card(DIAMONDS);

    ASSERT_EQUAL(test, queen_hearts);

    // Scenario 3: Leading with Ace of Spades as the last card
    test = alice->lead_card(DIAMONDS);

    // Alice is left with only the Ace of Spades, which should be led
    ASSERT_EQUAL(test, jack_spades);

    // Cleanup
    delete alice;
}

TEST(AllTrumpLead){
    Player *derek = Player_factory("Derek", "Simple");
    derek->add_card(nine_clubs);
    derek->add_card(ten_clubs);
    derek->add_card(jack_clubs);
    derek->add_card(queen_clubs);
    derek->add_card(king_clubs);

    Card test = derek->lead_card(CLUBS);

    ASSERT_EQUAL(test, king_clubs);

    delete derek;
}

TEST(PlayCardSimplePlayerScenario) {
    Player *bob = Player_factory("Bob", "Simple");

    // Scenario 1: Playing cards with different values as a Simple player
    bob->add_card(queen_clubs);
    bob->add_card(jack_clubs);
    bob->add_card(ten_diamonds);
    bob->add_card(ace_spades);
    bob->add_card(nine_hearts);

    // Lead with the Nine of Spades
    Card nine_spades = Card(NINE,SPADES);

    // Test playing cards in order of preference
    Card test = bob->play_card(nine_spades,SPADES);
    ASSERT_EQUAL(test, ace_spades);
    
    test = bob->play_card(ace_spades,SPADES);
    ASSERT_EQUAL(test, nine_hearts);
    delete bob;
}

TEST(MakeTrump){
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(queen_clubs);
    bob->add_card(jack_spades);
    bob->add_card(ten_spades);
    bob->add_card(ace_spades);
    bob->add_card(nine_hearts);

    Card up = Card(ACE, CLUBS);
    Suit ou_suit;
    bool make = bob->make_trump(up, false, 1, ou_suit);
    ASSERT_TRUE(make);
    ASSERT_EQUAL(ou_suit, CLUBS);

    up = queen_hearts;
    make = bob->make_trump(up, false, 1, ou_suit);
    ASSERT_FALSE(make);

    delete bob;
}

TEST(maketrumpedge){
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(queen_hearts);
    bob->add_card(jack_spades);
    bob->add_card(ten_spades);
    bob->add_card(ace_spades);
    bob->add_card(nine_spades);

    Card up = jack_diamonds;
    Suit ousuit;
    bool make = bob->make_trump(up, true, 2, ousuit);
    ASSERT_TRUE(make);
    ASSERT_EQUAL(ousuit, HEARTS);

    up = nine_clubs;
    make = bob->make_trump(up, true, 1, ousuit);
    ASSERT_FALSE(make);

    delete bob;
}

TEST_MAIN()
