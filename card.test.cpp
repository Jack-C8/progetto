#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "card.hpp"

#include "doctest.h"

TEST_CASE("Card construction") {
  el::Card c1("Hearts", "A", 11, true);
  el::Card c2("Diamonds", "A", 11, false);
  CHECK(c1.suit_ == "Hearts");
  CHECK(c1.range_ == "A");
  CHECK(c1.game_value_ == 11);
  CHECK(c1.face_ == true);
  CHECK(c2.face_ == false);
}

TEST_CASE("Deck basic construction") {
  el::Deck d1;
  el::Deck d2;

  SUBCASE("Deck Basics") {
    CHECK(d1.deck_size() == 156);
    CHECK(d2.deck_size() == d1.deck_size());

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

     for (size_t i = 0; i < d1.deck_size(); ++i) {
       CHECK(el::operator==(deck1[i], deck2[i]));
     }
  }

  SUBCASE("topCard method functions") {
    size_t initial_size = d1.deck_size();
    el::Card top = d1.topCard();
    CHECK(top.suit_ == "Diamonds");
    CHECK(top.range_ == "A");
    CHECK(top.game_value_ == 11);
    CHECK(top.face_ == true);
    CHECK(d1.deck_size() == (initial_size - 1));
    CHECK(d1.deck_size() == 155);
  }

  SUBCASE("topCard method multiple time") {
    el::Card top1 = d1.topCard();
    CHECK(d1.deck_size() == 155);
    CHECK(top1.game_value_ >= 2);
    CHECK(top1.game_value_ <= 11);

    el::Card top2 = d1.topCard();
    CHECK(d1.deck_size() == 154);
    CHECK(top2.game_value_ >= 2);
    CHECK(top2.game_value_ <= 11);
  }
  SUBCASE("Not enough cards, reset the game!") {
    size_t count = (d1.deck_size() - 30);
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
  SUBCASE("Draw the last constructed card") {
    el::Card card{"Diamonds", "A", 11, true};
    CHECK(d1.topCard() == card);
    CHECK(d1.deck_size() == 155);
  }
}
