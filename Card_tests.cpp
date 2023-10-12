#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

// Test constructor and getters
TEST(testConstructorAndGetters) {
    Card card(TEN, HEARTS);
    ASSERT_EQUAL(card.get_rank(), TEN);
    ASSERT_EQUAL(card.get_suit(), HEARTS);
    cout << "testConstructorAndGetters PASSED" << endl;
}

// Test get_suit(Suit trump)
TEST(testGetSuit) {
    Card card(TEN, HEARTS);
    ASSERT_EQUAL(card.get_suit(CLUBS), HEARTS);
    ASSERT_EQUAL(card.get_suit(HEARTS), HEARTS);  // Left bower, trump is HEARTS
    cout << "testGetSuit PASSED" << endl;
}

// Test is_face_or_ace()
TEST(testIsFaceOrAce) {
    Card faceCard(JACK, DIAMONDS);
    Card aceCard(ACE, SPADES);
    ASSERT_EQUAL(faceCard.is_face_or_ace(), true);
    ASSERT_EQUAL(aceCard.is_face_or_ace(), true);
    cout << "testIsFaceOrAce PASSED" << endl;
}

// Test is_right_bower(Suit trump)
TEST(testIsRightBower) {
    Card rightBower(JACK, HEARTS);
    ASSERT_EQUAL(rightBower.is_right_bower(HEARTS), true);
    ASSERT_EQUAL(rightBower.is_right_bower(DIAMONDS), false);
    cout << "testIsRightBower PASSED" << endl;
}

// Test is_left_bower(Suit trump)
TEST(testIsLeftBower) {
    Card leftBower(JACK, CLUBS);
    ASSERT_EQUAL(leftBower.is_left_bower(SPADES), true);
    ASSERT_EQUAL(leftBower.is_left_bower(CLUBS), false);
    cout << "testIsLeftBower PASSED" << endl;
}

// Test is_trump(Suit trump)
TEST(testIsTrump) {
    Card trumpCard(KING, CLUBS);
    ASSERT_EQUAL(trumpCard.is_trump(HEARTS), false);
    ASSERT_EQUAL(trumpCard.is_trump(CLUBS), true);  // Trump suit is CLUBS
    cout << "testIsTrump PASSED" << endl;
}

TEST(testOperatorStreamOutput) {
    Card card(TWO, SPADES);
    std::ostringstream oss;
    oss << card;
    ASSERT_EQUAL(oss.str(), "Two of Spades");
    cout << "testOperatorStreamOutput PASSED" << endl;
}

// Test operator>>
TEST(testOperatorStreamInput) {
    std::istringstream iss("Three of Hearts");
    Card card;
    iss >> card;
    ASSERT_EQUAL(card.get_rank(), THREE);
    ASSERT_EQUAL(card.get_suit(), HEARTS);
    cout << "testOperatorStreamInput PASSED" << endl;
}

// Test operator<
TEST(testOperatorLess) {
    Card card1(TWO, SPADES);
    Card card2(THREE, HEARTS);
    ASSERT_TRUE(card1 < card2);
    ASSERT_TRUE(!(card2 < card1));
    cout << "testOperatorLess PASSED" << endl;
}

// Test operator<=
TEST(testOperatorLessOrEqual) {
    Card card1(JACK, DIAMONDS);
    Card card2(KING, SPADES);
    Card card3(KING, SPADES);

    ASSERT_TRUE(card1 <= card2);
    ASSERT_FALSE(card2 <= card1);
    ASSERT_TRUE(card2 <= card3);
    cout << "testOperatorLessOrEqual PASSED" << endl;
}

// Test operator>
TEST(testOperatorGreater) {
    Card card1(TEN, CLUBS);
    Card card2(JACK, CLUBS);
    ASSERT_TRUE(card2 > card1);
    ASSERT_TRUE(!(card1 > card2));
    cout << "testOperatorGreater PASSED" << endl;
}

// Test operator>=
TEST(testOperatorGreaterOrEqual) {
    Card card1(ACE, HEARTS);
    Card card2(KING, HEARTS);
    Card card3(ACE, HEARTS);

    ASSERT_TRUE(card1 >= card2);
    ASSERT_FALSE(card2 >= card1);
    ASSERT_TRUE(card1 >= card3);
    cout << "testOperatorGreaterOrEqual PASSED" << endl;
}

// Test operator==
TEST(testOperatorEqual) {
    Card card1(QUEEN, SPADES);
    Card card2(KING, SPADES);
    Card card3(QUEEN, SPADES);

    (card1 == card3);
    ASSERT_TRUE(!(card1 == card2));
    cout << "testOperatorEqual PASSED" << endl;
}

// Test operator!=
TEST(testOperatorNotEqual) {
    Card card1(THREE, DIAMONDS);
    Card card2(TWO, HEARTS);
    ASSERT_TRUE(card1 != card2);
    cout << "testOperatorNotEqual PASSED" << endl;
}

// Test Suit_next
TEST(testSuitNext) {
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    cout << "testSuitNext PASSED" << endl;
}

// Test Card_less
TEST(testCardLess) {
    Card card1(TEN, SPADES);
    Card card2(QUEEN, HEARTS);
    Card card3(JACK, HEARTS);
    Suit trump = HEARTS;
    ASSERT_TRUE(Card_less(card1, card2, trump));
    ASSERT_FALSE(Card_less(card2, card1, trump));
    ASSERT_FALSE(Card_less(card2, card3, trump));
    cout << "testCardLess PASSED" << endl;
}

// Test Card_less with led_card
TEST(testCardLessWithLedCard) {
    Card ledCard(TWO, CLUBS);
    Card card1(TWO, SPADES);
    Card card2(QUEEN, CLUBS);
    Suit trump = CLUBS;
    ASSERT_TRUE(Card_less(card1, card2, ledCard, trump));
    ASSERT_TRUE(!Card_less(card2, card1, ledCard, trump));
    cout << "testCardLessWithLedCard PASSED" << endl;
}

TEST_MAIN()
