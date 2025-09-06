#include "methods.hpp"
#include "doctest.h"

namespace el {

TEST_CASE("GameState constructors") {
  SUBCASE("Default constructor initializes hands and score") {
    GameState gs;
    CHECK(gs.getYourHand().handSize() == 2);
    CHECK(gs.getYourScore() == gs.getYourHand().handScore());
    CHECK(gs.getPhases()[0] == true);
  }

  SUBCASE("Constructor with fishes initializes correctly") {
    GameState gs(500.f);
    CHECK(gs.getYourHand().handSize() == 2);
    CHECK(gs.getYourScore() == gs.getYourHand().handScore());
  }
}

TEST_CASE("GameState resetRound") {
  GameState gs;
  auto before = gs.getYourHand().handElement(0);
  gs.resetRound(300.f);
  auto after = gs.getYourHand().handElement(0);
  CHECK(gs.getYourHand().handSize() == 2);
  CHECK(gs.getYourScore() == gs.getYourHand().handScore());
}

TEST_CASE("advanceTurn changes phases correctly") {
  GameState gs;
  CHECK(gs.getPhases()[0] == true);
  gs.advanceTurn(0);
  CHECK(gs.getPhases()[0] == false);
  CHECK(gs.getPhases()[1] == true);
}

TEST_CASE("Dealer, Bot1 and Bot2 play according to rules") {
  GameState gs;

  SUBCASE("Dealer stops at 17 or more") {
    gs.dealerPlay();
    CHECK(gs.getDealerHand().handScore() >= 17);
  }

  SUBCASE("Bot1 stops at 17 or more") {
    gs.bot1Play();
    CHECK(gs.getBot1Hand().handScore() >= 17);
  }

  SUBCASE("Bot2 stops at 18 or more") {
    gs.bot2Play();
    CHECK(gs.getBot2Hand().handScore() >= 18);
  }
}

TEST_CASE("calculatePayout updates fishes correctly") {
  float fishes = 100.f;
  int bet = 10;
  fishes -= static_cast<float>(bet);

  SUBCASE("Blackjack pays 2.5x") {
    GameState gs;
    Hand bj(Card("Hearts", "A", 11), Card("Spades", "K", 10));
    gs.getYourHand() = bj;
    gs.calculatePayout(fishes, bet);
    CHECK(fishes == doctest::Approx(115.f)); 
    CHECK(gs.you_won == true);
  }

  SUBCASE("Player wins with higher score") {
    GameState gs;
    gs.getYourHand() =
        Hand(Card("Hearts", "9", 9), Card("Spades", "9", 9));  
    gs.getDealerHand() =
        Hand(Card("Clubs", "9", 9), Card("Diamonds", "8", 8)); 
    gs.calculatePayout(fishes, bet);
    CHECK(fishes == doctest::Approx(110.f));
    CHECK(gs.you_won == true);
  }

  SUBCASE("Dealer bust means player wins") {
    GameState gs;
    gs.getYourHand() =
        Hand(Card("Hearts", "9", 9), Card("Spades", "9", 9)); 
    gs.getDealerHand() =
        Hand(Card("Clubs", "K", 10), Card("Diamonds", "K", 10));
    gs.getDealerHand().addCard(Card("Hearts", "5", 5));
    gs.calculatePayout(fishes, bet);
    CHECK(fishes == doctest::Approx(110.f));
    CHECK(gs.you_won == true);
  }

  SUBCASE("Draw keeps the bet") {
    GameState gs;
    gs.getYourHand() =
        Hand(Card("Hearts", "10", 10), Card("Spades", "9", 9));  
    gs.getDealerHand() =
        Hand(Card("Clubs", "K", 10), Card("Diamonds", "9", 9));  
    gs.calculatePayout(fishes, bet);
    CHECK(fishes == doctest::Approx(100.f));
    CHECK(gs.draw == true);
  }

  SUBCASE("Player loses bet if lower than dealer") {
    GameState gs;
    gs.getYourHand() =
        Hand(Card("Hearts", "7", 7), Card("Spades", "9", 9));  
    gs.getDealerHand() =
        Hand(Card("Clubs", "10", 10), Card("Diamonds", "9", 9));  
    gs.calculatePayout(fishes, bet);
    CHECK(fishes == doctest::Approx(90.f));  
    CHECK(gs.you_won == false);
    CHECK(gs.draw == false);
  }
}
}  // namespace el
