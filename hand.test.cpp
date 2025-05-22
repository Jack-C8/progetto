#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "hand.hpp"
#include "card.hpp"

#include "doctest.h"

TEST_CASE("Testing the Hand class methods") {
  el::Hand hand{};
  CHECK(hand.size() == 0);

  el::Card c1{"Hearts", "A", 11, true};
  el::Card c2{"Clubs", "5", 5, true};
  el::Hand hand1{c1, c2};
  CHECK(hand1.size() == 2);

  el::Card c3{"Spades", "3", 3, true};
  el::Card c4{"Diamonds", "8", 8, true};
  el::Hand hand2{c3, c4};
  CHECK(hand2.size() == 2);

  CHECK(hand1.element(0) == c1);
  CHECK(hand1.element(1) == c2);
  CHECK(hand2.element(0) == c3);
  CHECK(hand2.element(1) == c4);

  el::Deck deck{};
  hand.hand_draw(deck);
  CHECK(hand.size() == 1);
  hand.hand_draw(deck);
  CHECK(hand.size() == 2);
  hand.hand_draw(deck);
  CHECK(hand.size() == 3);
  hand.hand_draw(deck);
  CHECK(hand.size() == 4);

  for (int i{}; i <= 50; ++i) {
    hand.hand_draw(deck);
  }
  CHECK(hand.size() == 54);
}