#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "card.hpp"

#include "doctest.h"

TEST_CASE("Deck basic construction") {
  el::Deck d1;
  el::Deck d2;

  SUBCASE("Deck Basics") {
    CHECK(d1.size() == 156);
    CHECK(d2.size() == d1.size());

    const auto deck1 = d1.get_deck();
    const auto deck2 = d2.get_deck();

    CHECK(deck1[0].suit_ == "Hearts");
    CHECK(deck1[0].range_ == "2");
    CHECK(deck1[0].game_value_ == 2);
    CHECK(deck1[0].face_ == true);
    CHECK(deck1[0].suit_ == deck2[0].suit_);
    CHECK(deck1[0].range_ == deck2[0].range_);
    CHECK(deck1[0].game_value_ == deck2[0].game_value_);
    CHECK(deck1[0].face_ == deck2[0].face_);
  }

  SUBCASE("Deck construction create the same deck") {
    const auto deck1 = d1.get_deck();
    const auto deck2 = d2.get_deck();

    for (size_t i = 0; i < d1.size(); ++i) {
      CHECK(el::operator==(deck1[i], deck2[i]));
    }
  }

  SUBCASE("topCard method functions") {
    size_t initial_size = d1.size();
    el::Card top = d1.topCard();
    CHECK(top.suit_ == "Diamonds");
    CHECK(top.range_ == "A");
    CHECK(top.game_value_ == 11);
    CHECK(top.face_ == true);
    CHECK(d1.size() == (initial_size - 1));
    CHECK(d1.size() == 155);
  }

  SUBCASE("topCard method multiple time") {
    d1.topCard();
    CHECK(d1.size() == 155);

    d1.topCard();
    CHECK(d1.size() == 154);

    d1.topCard();
    d1.topCard();
    d1.topCard();
    d1.topCard();  // pesco le prime 6 carte e vedo se sono al punto giusto
    CHECK(d1.size() == 150);
    el::Card card1{"Diamonds", "10", 10, true};
    CHECK(d1.topCard() == card1);
    CHECK(d1.size() == 151);

    for (int i{}; i < 14; ++i) {
      d1.topCard();
    }                                     // pesco le prime 20 carte
    CHECK(d1.size() == 136);
    el::Card card2{"Spades", "7", 7, true};
    CHECK(d1.topCard() == card2);
    CHECK(d1.size() == 135);
  }

  SUBCASE("Not enough cards, reset the game!") {
    size_t count = (d1.size() - 30);
    for (size_t i = 0; i < count; ++i) {
      d1.topCard();
    }
    CHECK_THROWS_WITH(d1.topCard(), "Not enough cards, reset the game!");
  }
  SUBCASE("Card operator==") {
    el::Card c1{"Hearts", "2", 2, true};
    el::Card c2{"Hearts", "3", 3, true};
    el::Card c3{"Clubs", "2", 2, true};
    el::Card c4{"Hearts", "2", 3, true};
    el::Card c5{"Spades", "4", 4, true};
    CHECK((c1 == c1) == true);
    CHECK((c1 == c2) == false);
    CHECK((c1 == c3) == false);
    CHECK((c1 == c4) ==
          true);  // operator== non deve tener conto del game_value della carta
    CHECK((c1 == c5) == false);
  }
}