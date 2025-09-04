
#include "player.hpp"

#include "card.hpp"
#include "doctest.h"
#include "hand.hpp"
namespace el {

TEST_CASE("Player costruttore e stato iniziale") {
  Player p(PlayerType::Human, 500, 100);

  CHECK(p.getType() == PlayerType::Human);
  CHECK(p.getFishes() == doctest::Approx(500));
  CHECK(p.getBet() == doctest::Approx(100));
  CHECK(p.isStanding() == false);
  CHECK(p.getHand().handSize() == 0);
}

TEST_CASE("Player stand() imposta isStanding") {
  Player p(PlayerType::Bot1, 1000, 50);

  CHECK(p.isStanding() == false);
  p.stand();
  CHECK(p.isStanding() == true);
}

TEST_CASE("Player hit() aggiunge carte") {
  Deck deck;
  Player p(PlayerType::Bot2, 1000, 50);

  int before = p.getHand().handSize();
  p.hit(deck);
  CHECK(p.getHand().handSize() == before + 1);
}

TEST_CASE("Player doubleDown comportamenti") {
  Deck deck;

  SUBCASE("Double down con abbastanza fishes") {
    Player p(PlayerType::Bot1, 1000, 100);

    float initialFishes = p.getFishes();
    float initialBet = p.getBet();
    int initialSize = p.getHand().handSize();

    p.doubleDown(deck);

    CHECK(p.getBet() == doctest::Approx(initialBet * 2));
    CHECK(p.getFishes() == doctest::Approx(initialFishes - initialBet));
    CHECK(p.getHand().handSize() == initialSize + 1);
    CHECK(p.isStanding() == true);
  }

  SUBCASE("Double down senza abbastanza fishes deve lanciare eccezione") {
    Player p(PlayerType::Human, 50, 100);  // fishes < bet
    CHECK_THROWS_AS(p.doubleDown(deck), std::runtime_error);
    CHECK(p.isStanding() == false);
  }
}

TEST_CASE("Player hands con assi") {
  Player p(PlayerType::Human, 500, 100);
  SUBCASE("Asso + 9 = 20 (soft hand)") {
    Hand h(Card("Hearts", "A", 11), Card("Spades", "9", 9));
    p.getHand() = h;
    CHECK(p.getHand().handScore() == 20);
  }

  SUBCASE("Asso + Asso = 12 (uno dei due conta 1)") {
    Hand h(Card("Hearts", "A", 11), Card("Spades", "A", 11));
    p.getHand() = h;
    CHECK(p.getHand().handScore() == 12);
  }

  SUBCASE("Asso + 9 + 5 = 15 (Asso scala a 1)") {
    Hand h(Card("Hearts", "A", 11), Card("Spades", "9", 9));
    el::Card c1{"Clubs", "5", 5};
    h.addCard(c1);
    p.getHand() = h;
    CHECK(p.getHand().handScore() == 15);
  }

  SUBCASE("Asso + K = 21 (Blackjack)") {
    Hand h(Card("Hearts", "A", 11), Card("Spades", "K", 10));
    p.getHand() = h;
    CHECK(p.getHand().handScore() == 21);
    CHECK(p.getHand().blackjack() == true);
  }
}
}  // namespace el
