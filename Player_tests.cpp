#include "Player.hpp"
#include "unit_test_framework.hpp"
#include "Card.hpp"

#include <iostream>

using namespace std;

Card nine_spades = Card(NINE, SPADES);
Card ten_spades = Card(TEN, SPADES);
Card jack_spades = Card(JACK, SPADES);
Card queen_spades = Card(QUEEN, SPADES);
Card king_spades = Card(KING, SPADES);
Card ace_spades = Card(ACE, SPADES);
Card nine_clubs = Card(NINE, CLUBS);
Card ten_clubs = Card(TEN, CLUBS);
Card jack_clubs = Card(JACK, CLUBS);
Card queen_clubs = Card(QUEEN, CLUBS);
Card king_clubs = Card(KING, CLUBS);
Card ace_clubs = Card(ACE, CLUBS);
Card nine_hearts = Card(NINE, HEARTS);
Card ten_hearts = Card(TEN, HEARTS);
Card jack_hearts = Card(JACK, HEARTS);
Card queen_hearts = Card(QUEEN, HEARTS);
Card king_hearts = Card(KING, HEARTS);
Card ace_hearts = Card(ACE, HEARTS);
Card nine_diamonds = Card(NINE, DIAMONDS);
Card ten_diamonds = Card(TEN, DIAMONDS);
Card jack_diamonds = Card(JACK, DIAMONDS);
Card queen_diamonds = Card(QUEEN, DIAMONDS);
Card king_diamonds = Card(KING, DIAMONDS);
Card ace_diamonds = Card(ACE, DIAMONDS);
Card two_spades = Card(TWO, SPADES);
Card two_diamonds = Card(TWO, DIAMONDS);

// Helper function for creating a Simple player
Player* createSimplePlayerWithCards(const std::string& name, const std::vector<Card>& cards) {
    Player* player = Player_factory(name, "Simple");
    for (const Card& card : cards) {
        player->add_card(card);
    }
    return player;
}

TEST(test_player_get_name) {
    Player* alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(LeadCardSimplePlayerScenario) {
    // Scenario 1: Leading with Hearts as trump
    Player* alice = createSimplePlayerWithCards("Alice", {queen_hearts, jack_spades, ace_spades});

    Card test = alice->lead_card(HEARTS);
    ASSERT_EQUAL(test, ace_spades);

    test = alice->lead_card(DIAMONDS);
    ASSERT_EQUAL(test, queen_hearts);

    // Scenario 3: Leading with Ace of Spades as the last card
    Player* bob = createSimplePlayerWithCards("Bob", {ace_spades});

    test = bob->lead_card(DIAMONDS);
    // Bob is left with only the Ace of Spades, which should be led
    ASSERT_EQUAL(test, ace_spades);

    // Cleanup
    delete alice;
    delete bob;
}

TEST(AllTrumpLeadHighestClub) {
    // Arrange: Create a Simple player named Derek with Club cards
    Player* derek = createSimplePlayerWithCards("Derek", {nine_clubs, ten_clubs, jack_clubs, queen_clubs, king_clubs});

    // Act: Derek leads with Clubs as the trump suit
    Card test = derek->lead_card(CLUBS);

    // Assert: The highest-ranked Club card should be led
    ASSERT_EQUAL(test, king_clubs);

    // Cleanup
    delete derek;
}

TEST(PlayCardSimplePlayerScenario) {
    // Scenario 1: Playing cards with different values as a Simple player
    Player* bob = createSimplePlayerWithCards("Bob", {queen_clubs, jack_clubs, ten_diamonds, ace_spades, nine_hearts});

    // Lead with the Nine of Spades
    Card nine_spades = Card(NINE, SPADES);

    // Test playing cards in order of preference
    Card test = bob->play_card(nine_spades, SPADES);
    ASSERT_EQUAL(test, ace_spades);
    
    test = bob->play_card(ace_spades, SPADES);
    ASSERT_EQUAL(test, nine_hearts);

    // Cleanup
    delete bob;
}

TEST(MakeTrump) {
    // Scenario 1: Making trump with Ace of Clubs
    Player* bob = createSimplePlayerWithCards("Bob", {queen_clubs, jack_spades, ten_spades, ace_spades, nine_hearts});
    Card up = Card(ACE, CLUBS);
    Suit ou_suit;
    bool make = bob->make_trump(up, false, 1, ou_suit);
    ASSERT_FALSE(make);
    delete bob;

    // Scenario 2: Passing with no suitable cards
    Player* charlie = createSimplePlayerWithCards("Charlie", {queen_hearts, jack_spades, ten_spades, ace_spades, nine_hearts});
    up = queen_hearts;
    make = charlie->make_trump(up, false, 1, ou_suit);
    ASSERT_FALSE(make);
    delete charlie;
}

TEST(MakeTrumpEdgeCases) {
    // Scenario 1: Making trump with Jack of Diamonds, Two of Hearts as trump, and 2 cards left
    Player* dave = createSimplePlayerWithCards("Dave", {queen_hearts, jack_spades, ten_spades, ace_spades, two_spades});
    Card up = jack_diamonds;
    Suit ou_suit;
    bool make = dave->make_trump(up, true, 2, ou_suit);
    ASSERT_TRUE(make);
    ASSERT_EQUAL(ou_suit, HEARTS);
    delete dave;

    // Scenario 2: Passing with no suitable cards
    Player* ed = createSimplePlayerWithCards("Ed", {queen_clubs, jack_spades, ten_spades, ace_spades, nine_spades});
    up = nine_clubs;
    make = ed->make_trump(up, true, 1, ou_suit);
    ASSERT_FALSE(make);
    delete ed;
}

TEST_MAIN()