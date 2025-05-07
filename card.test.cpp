#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "card.hpp"

#include "doctest.h"

TEST_CASE("Card construction") {
  el::Card c1("Hearts", "A", 11);
  el::Card c2("Clubs", "2", 2, false);
  CHECK(c1.suit == "Hearts");
  CHECK(c1.range == "A");
  CHECK(c1.game_value == 11);
  CHECK(c1.face == true);
  CHECK(c2.face == false);
}

TEST_CASE("Deck basic construction") {
  el::Deck d1;
  el::Deck d2;

  SUBCASE("Deck Basics") {
    CHECK(d1.deck_size() == 156);
    CHECK(d2.deck_size() == d1.deck_size());

    const auto deck1 = d1.get_deck();
    const auto deck2 = d2.get_deck();
    CHECK(deck1[0].suit == "Hearts");
    CHECK(deck1[0].range == "2");
    CHECK(deck1[0].game_value == 2);
    CHECK(deck1[0].face == true);
    CHECK(deck1[0].suit == deck2[0].suit);
    CHECK(deck1[0].range == deck2[0].range);
    CHECK(deck1[0].game_value == deck2[0].game_value);
    CHECK(deck1[0].face == deck2[0].face);
  }

  // SUBCASE("Deck construction create the same deck") {
  //   const auto deck1 = d1.get_deck();
  //   const auto deck2 = d2.get_deck();

  //   for (size_t i = 0; i < d1.deck_size(); ++i) {
  //     CHECK(el::operator==(deck1[i], deck2[i]));
  //   }
  // }

  SUBCASE("topCard method functions") {
    size_t initial_size = d1.deck_size();
    el::Card top = d1.topCard();
    CHECK(top.suit == "Diamonds");
    CHECK(top.range == "A");
    CHECK(top.game_value == 11);
    CHECK(top.face == true);
    CHECK(d1.deck_size() == (initial_size - 1));
    CHECK(d1.deck_size() == 155);
  }
  SUBCASE("topCard method multiple time") {
    el::Card top1 = d1.topCard();
    CHECK(d1.deck_size() == 155);
    CHECK(top1.game_value >= 2);
    CHECK(top1.game_value <= 11);

    el::Card top2 = d1.topCard();
    CHECK(d1.deck_size() == 154);
    CHECK(top2.game_value >= 2);
    CHECK(top2.game_value <= 11);
  }
  SUBCASE("Not enough cards, reset the game!") {
    size_t count = (d1.deck_size() - 30);
    for (size_t i = 0; i < count; ++i) {
      d1.topCard();
    }
    CHECK_THROWS_WITH(d1.topCard(), "Not enough cards, reset the game!");
  }
}

/*
inline bool operator!=(Card const& left, Card const& right) {
  return left.suit != right.suit || left.range != right.range;
}
aggiungo qui la ri-definizione di == perché all'interno del gioco
è inutile ma molto utile per i vari test da fare sulle carte e sulle funzioni.*/