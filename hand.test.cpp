#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "hand.hpp"
#include "card.hpp"
#include "methods.hpp"
#include "doctest.h"

TEST_CASE("Testing the Hand class methods") {
  el::Deck deck{};
  el::Hand hand{};
  el::Card c1{"Hearts", "A", 11, true};
  el::Card c2{"Clubs", "5", 5, true};
  el::Hand hand1{c1, c2};
  el::Card c3{"Spades", "3", 3, true};
  el::Card c4{"Diamonds", "8", 8, true};
  el::Hand hand2{c3, c4};
  el::Card c5{"Diamonds", "J", 10, true};
  el::Card c6{"Clubs", "A", 11, true};
  el::Hand hand3{c5, c6};
  el::Hand hand4{c5, c5};

  SUBCASE("Hand basics: size, element and score") {
    CHECK(hand.hand_size() == 0);
    CHECK(hand1.hand_size() == 2);
    CHECK(hand1.hand_element(1) == c2);
    CHECK(hand2.hand_size() == 2);
    CHECK(hand1.hand_element(0) == c1);
    CHECK(hand1.hand_element(1) == c2);
    CHECK(hand2.hand_element(0) == c3);
    CHECK(hand2.hand_element(1) == c4);
    CHECK(hand1.hand_score() == 16);
    CHECK(hand2.hand_score() == 11);
  }

  SUBCASE("Hand remove, add, blackjack and split") {
    hand1.remove_card();
    CHECK(hand1.hand_size() == 1);
    CHECK(hand1.hand_element(0) == c1);
    CHECK(hand1.hand_score() == 11);
    CHECK(hand1.blackjack() == false);

    hand.add_card(c2);
    hand.add_card(c3);
    CHECK(hand.hand_size() == 2);
    CHECK(hand.hand_score() == 8);

    hand.add_card(c1);
    CHECK(hand.hand_size() == 3);
    CHECK(hand.hand_score() == 19);
    hand.add_card(c4);
    CHECK(hand.hand_size() == 4);
    CHECK(hand.hand_score() == 20);

    CHECK(hand3.hand_score() == 21);
    CHECK(hand3.blackjack() == true);
    CHECK(hand.cansplit() == false);

    CHECK(hand4.hand_score() == 20);
    CHECK(hand4.cansplit() == true);
    hand4.add_card(c1);
    CHECK(hand4.hand_score() == 21);
    CHECK(hand4.blackjack() == false);

    el::Hand splitted = split(hand4, deck);
    CHECK(splitted.hand_size() == 2);
    CHECK(splitted.hand_score() == 21);
    CHECK(splitted.blackjack() == true);
    CHECK(hand4.hand_size() == 2);
    CHECK(hand4.hand_score() == 20);
    CHECK(hand4.cansplit() == true);
    hand4.add_card(c3);
    CHECK(hand4.hand_score() == 23);
    CHECK(hand4.blackjack() == false);
  }

  SUBCASE("All throws of the class") {
    CHECK_THROWS_WITH(hand3.add_card(c3),
                      "You can't hit, your score is the highest possible");
    CHECK_THROWS_WITH(split(hand3, deck), "You can't split these cards!");
    CHECK_THROWS_WITH(hand3.hand_draw(deck),
                      "You can't hit, your score is the highest possible");
    hand.add_card(c5);
    hand.add_card(c3);
    CHECK_THROWS_WITH(hand.add_card(c3),
                      "You can't hit, your score is the highest possible");
  }
}