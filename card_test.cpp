#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "card.hpp"

#include "doctest.h"

namespace el {

TEST_CASE("Card basics") {
  SUBCASE("Card construction and getters") {
    Card c("Hearts", "A", 11);
    CHECK(c.getSuit() == "Hearts");
    CHECK(c.getRange() == "A");
    CHECK(c.getGameValue() == 11);
  }

  SUBCASE("Equality operator - same suit and range") {
    Card c1("Spades", "K", 10);
    Card c2("Spades", "K", 10);
    CHECK(c1 == c2);
  }

  SUBCASE("Equality operator - different suit or range") {
    Card c1("Diamonds", "Q", 10);
    Card c2("Clubs", "Q", 10);
    Card c3("Diamonds", "J", 10);
    CHECK_FALSE(c1 == c2);
    CHECK_FALSE(c1 == c3);
  }
}

TEST_CASE("Deck construction") {
  Deck d;
  SUBCASE("Initial size is 156 cards (3 decks)") { CHECK(d.size() == 156); }

  SUBCASE("Contains expected suits and ranges") {
    bool hasAceHearts = false;
    for (const auto& c : d.getDeck()) {
      if (c.getSuit() == "Hearts" && c.getRange() == "A") {
        hasAceHearts = true;
        break;
      }
    }
    CHECK(hasAceHearts);
  }
}

TEST_CASE("Deck shuffle") {
  Deck d1, d2;
  d1.shuffle();
  d2.shuffle();
  SUBCASE("Shuffle does not change deck size") { CHECK(d1.size() == 156); }
  SUBCASE("Shuffle changes order (likely)") {
    bool sameOrder = true;
    for (size_t i = 0; i < d1.size(); ++i) {
      if (!(d1.getDeck()[i] == d2.getDeck()[i])) {
        sameOrder = false;
        break;
      }
    }
    CHECK(sameOrder == false);
  }
}

TEST_CASE("Deck topCard") {
  Deck d;
  size_t initialSize = d.size();

  SUBCASE("topCard reduces deck size by 1") {
    Card c = d.topCard();
    CHECK(d.size() == initialSize - 1);
  }

  SUBCASE("Throws when <= 30 cards left") {
    while (d.size() > 30) {
      d.topCard();
    }
    CHECK_THROWS_AS(d.topCard(), std::runtime_error);
  }
}

TEST_CASE("Deck getDeck consistency") {
  Deck d;
  const auto& cards = d.getDeck();
  SUBCASE("getDeck reference size matches deck size") {
    CHECK(cards.size() == d.size());
  }
}
}  // namespace el