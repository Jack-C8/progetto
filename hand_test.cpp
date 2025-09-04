#include "hand.hpp"

#include "card.hpp"
#include "doctest.h"

TEST_CASE("Testing the Hand class methods") {
  el::Deck deck{};
  el::Hand hand{};
  el::Card c1{"Hearts", "A", 11};
  el::Card c2{"Clubs", "5", 5};
  el::Hand hand1{c1, c2};
  el::Card c3{"Spades", "3", 3};
  el::Card c4{"Diamonds", "8", 8};
  el::Hand hand2{c3, c4};
  el::Card c5{"Diamonds", "J", 10};
  el::Card c6{"Clubs", "A", 11};
  el::Hand hand3{c5, c6};
  el::Hand hand4{c5, c5};

  SUBCASE("Hand basics: size, element and score") {
    CHECK(hand.handSize() == 0);
    CHECK(hand1.handSize() == 2);
    CHECK(hand1.handElement(1) == c2);
    CHECK(hand2.handSize() == 2);
    CHECK(hand1.handElement(0) == c1);
    CHECK(hand1.handElement(1) == c2);
    CHECK(hand2.handElement(0) == c3);
    CHECK(hand2.handElement(1) == c4);
    CHECK(hand1.handScore() == 16);
    CHECK(hand2.handScore() == 11);
  }

  SUBCASE("Hand remove, add, blackjack and split") {
    hand1.removeCard();
    CHECK(hand1.handSize() == 1);
    CHECK(hand1.handElement(0) == c1);
    CHECK(hand1.handScore() == 11);
    CHECK(hand1.blackjack() == false);

    hand.addCard(c2);
    hand.addCard(c3);
    CHECK(hand.handSize() == 2);
    CHECK(hand.handScore() == 8);

    hand.addCard(c1);
    CHECK(hand.handSize() == 3);
    CHECK(hand.handScore() == 19);
    hand.addCard(c4);
    CHECK(hand.handSize() == 4);
    CHECK(hand.handScore() == 17);

    CHECK(hand3.handScore() == 21);
    CHECK(hand3.blackjack() == true);

    CHECK(hand4.handScore() == 20);
    hand4.addCard(c1);
    CHECK(hand4.handScore() == 21);
    CHECK(hand4.blackjack() == false);
  }

  SUBCASE("All throws of the class") {
    CHECK_THROWS_WITH(hand3.addCard(c3),
                      "You can't hit, your score is the highest possible");
    CHECK_THROWS_WITH(hand3.handDraw(deck),
                      "You can't hit, your score is the highest possible");
    hand.addCard(c5);
    hand.addCard(c3);
    hand.addCard(c5);
    CHECK_THROWS_WITH(hand.addCard(c2),
                      "You can't hit, your score is the highest possible");
  }
}