
#include "hand.hpp"
#include <stdexcept>

#include "card.hpp"
#include "doctest.h"

namespace el {

TEST_CASE("Hand basic functionality with real Card and Deck") {
  Card aceSpades("Spades", "A", 11);
  Card kingHearts("Hearts", "K", 10);
  Card twoClubs("Clubs", "2", 2);
  Card nineDiamonds("Diamonds", "9", 9);

  SUBCASE("Constructor with two cards forms Blackjack") {
    Hand h(aceSpades, kingHearts);
    CHECK(h.handSize() == 2);
    CHECK(h.handScore() == 21);
    CHECK(h.blackjack() == true);
  }

  SUBCASE("Empty hand and addCard") {
    Hand h;
    h.addCard(twoClubs);
    h.addCard(nineDiamonds);
    CHECK(h.handSize() == 2);
    CHECK(h.handScore() == 11);
    CHECK_FALSE(h.blackjack());
  }

  SUBCASE("Ace counts as 1 if total > 21") {
    Hand h;
    h.addCard(aceSpades);
    h.addCard(nineDiamonds);
    h.addCard(twoClubs);
    CHECK(h.handScore() == 12);
  }

  SUBCASE("addCard throws if score is already 21") {
    Hand h(kingHearts, kingHearts);
    h.addCard(aceSpades);
    CHECK_THROWS_WITH(h.addCard(twoClubs),
                      "You can't hit, your score is the highest possible");
  }

  SUBCASE("removeCard decreases hand size") {
    Hand h(aceSpades, twoClubs);
    CHECK(h.handSize() == 2);
    h.removeCard();
    CHECK(h.handSize() == 1);
  }

  SUBCASE("handElement returns correct card") {
    Hand h(kingHearts, nineDiamonds);
    Card c = h.handElement(0);
    CHECK(c == kingHearts);
  }

  SUBCASE("handDraw throws if score >= 21") {
    Deck d;
    Hand h(kingHearts, kingHearts);
    h.addCard(aceSpades);
    CHECK_THROWS_WITH(h.handDraw(d),
                      "You can't hit, your score is the highest possible");
  }
}
TEST_CASE("Additional Hand logic tests") {
  Card aceHearts("Hearts", "A", 11);
  Card aceClubs("Clubs", "A", 11);
  Card aceSpades("Spades", "A", 11);
  Card kingDiamonds("Diamonds", "K", 10);
  Card fiveClubs("Clubs", "5", 5);

  SUBCASE("Multiple Aces are handled correctly") {
    Hand h;
    h.addCard(aceHearts);
    h.addCard(aceClubs);
    CHECK(h.handScore() == 12);

    h.addCard(aceSpades);
    CHECK(h.handScore() == 13);
  }

  SUBCASE("Multiple Aces + 10 valued card") {
    Hand h;
    h.addCard(aceHearts);
    h.addCard(aceClubs);
    h.addCard(kingDiamonds);
    CHECK(h.handScore() == 12);
  }

  SUBCASE("Hand goes bust with no Aces") {
    Hand h;
    h.addCard(kingDiamonds);
    h.addCard(kingDiamonds);
    h.addCard(fiveClubs);
    CHECK(h.handScore() == 25);
  }

  SUBCASE("Multiple removeCard calls") {
    Hand h;
    h.addCard(kingDiamonds);
    h.addCard(fiveClubs);
    CHECK(h.handSize() == 2);

    h.removeCard();
    CHECK(h.handSize() == 1);

    h.removeCard();
    CHECK(h.handSize() == 0);
  }
}
}  // namespace el