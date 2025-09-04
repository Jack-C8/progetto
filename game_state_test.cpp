
#include "game_state.hpp"

#include "card.hpp"
#include "doctest.h"
#include "hand.hpp"
#include "player.hpp"

 namespace el{

TEST_CASE("Bot1 logic") {
  GameState gs(500, 100);
  auto& bot1 = gs.getPlayers()[0];
  auto& dealer = gs.getPlayers().back();

  SUBCASE("Double down se punteggio 10 e dealer < 6") {
    bot1.getHand() = Hand(Card("Hearts", "5", 5), Card("Spades", "5", 5));  // 10
    dealer.getHand() = Hand(Card("Clubs", "4", 4), Card("Diamonds", "10", 10));

    float initialFishes = bot1.getFishes();
    float initialBet = bot1.getBet();

    gs.botLogic1(bot1, dealer.getHand());

    CHECK(bot1.getBet() == doctest::Approx(initialBet * 2));
    CHECK(bot1.getFishes() == doctest::Approx(initialFishes - initialBet));
    CHECK(bot1.isStanding() == true);
  }

  SUBCASE("Punteggio basso (<5): deve pescare 3 carte") {
    bot1.getHand() = Hand(Card("Hearts", "2", 2), Card("Spades", "2", 2));  // 4
    int initialSize = bot1.getHand().handSize();

    gs.botLogic1(bot1, dealer.getHand());

    CHECK(bot1.getHand().handSize() >= initialSize + 3);
    CHECK(bot1.isStanding() == true);
  }

  SUBCASE("Default: continua a pescare fino a >=15") {
    bot1.getHand() = Hand(Card("Hearts", "7", 7), Card("Spades", "2", 2));  // 9
    gs.botLogic1(bot1, dealer.getHand());

    CHECK(bot1.getHand().handScore() >= 15);
    CHECK(bot1.isStanding() == true);
  }
   SUBCASE("Mano con A+2 (soft 13): deve pescare fino a 15") {
        bot1.getHand() = Hand(Card("Hearts", "A", 11), Card("Spades", "2", 2));
        gs.botLogic1(bot1, dealer.getHand());

        CHECK(bot1.getHand().handScore() >= 15);
        CHECK(bot1.isStanding() == true);
    }
}

TEST_CASE("Bot2 logic") {
  GameState gs(500, 100);
  auto& bot2 = gs.getPlayers()[2];
  auto& dealer = gs.getPlayers().back();

  SUBCASE("Double down se punteggio 11 e dealer < 8") {
    bot2.getHand() = Hand(Card("Hearts", "6", 6), Card("Spades", "5", 5));  // 11
    dealer.getHand() = Hand(Card("Clubs", "7", 7), Card("Diamonds", "10", 10));

    float initialFishes = bot2.getFishes();
    float initialBet = bot2.getBet();

    gs.botLogic2(bot2, dealer.getHand());

    CHECK(bot2.getBet() == doctest::Approx(initialBet * 2));
    CHECK(bot2.getFishes() == doctest::Approx(initialFishes - initialBet));
    CHECK(bot2.isStanding() == true);
  }

  SUBCASE("Punteggio basso (<5): deve pescare 3 carte") {
    bot2.getHand() = Hand(Card("Hearts", "2", 2), Card("Spades", "2", 2));  // 4
    int initialSize = bot2.getHand().handSize();

    gs.botLogic2(bot2, dealer.getHand());

    CHECK(bot2.getHand().handSize() >= initialSize + 3);
    CHECK(bot2.isStanding() == true);
  }

  SUBCASE("Caso speciale: punteggio 7 e dealer <9: hit + double down") {
    bot2.getHand() = Hand(Card("Hearts", "3", 3), Card("Spades", "4", 4));  // 7
    dealer.getHand() = Hand(Card("Clubs", "8", 8), Card("Diamonds", "10", 10));

    float initialFishes = bot2.getFishes();
    float initialBet = bot2.getBet();

    gs.botLogic2(bot2, dealer.getHand());

    CHECK(bot2.getBet() >= initialBet * 2);  // ha fatto double down
    CHECK(bot2.getFishes() <= initialFishes - initialBet);
    CHECK(bot2.isStanding() == true);
  }

  SUBCASE("Default: continua a pescare fino a >=17") {
    bot2.getHand() = Hand(Card("Hearts", "9", 9), Card("Spades", "2", 2));  // 11
    gs.botLogic2(bot2, dealer.getHand());

    CHECK(bot2.getHand().handScore() >= 17);
    CHECK(bot2.isStanding() == true);
  }
    SUBCASE("Mano con A+6 (soft 17): deve stare") {
        bot2.getHand() = Hand(Card("Hearts", "A", 11), Card("Spades", "6", 6));
        gs.botLogic2(bot2, dealer.getHand());

        CHECK(bot2.getHand().handScore() >= 17);
        CHECK(bot2.isStanding() == true);
    }

    SUBCASE("Mano con A+3 (soft 14): deve pescare fino a >=17") {
        bot2.getHand() = Hand(Card("Hearts", "A", 11), Card("Spades", "3", 3));
        gs.botLogic2(bot2, dealer.getHand());

        CHECK(bot2.getHand().handScore() >= 17);
        CHECK(bot2.isStanding() == true);
    }
}
TEST_CASE("Dealer logic") {
  GameState gs(500, 100);
  auto& dealer = gs.getPlayers().back();

  SUBCASE("Dealer parte con punteggio basso (<17): deve pescare") {
    dealer.getHand() = Hand(Card("Hearts", "2", 2), Card("Spades", "3", 3));  // 5
    gs.dealerLogic(dealer);

    CHECK(dealer.getHand().handScore() >= 17);
    CHECK(dealer.isStanding() == true);
  }

  SUBCASE("Dealer parte già con 17: non deve pescare") {
    dealer.getHand() =
        Hand(Card("Hearts", "10", 10), Card("Spades", "7", 7));  // 17
    int initialSize = dealer.getHand().handSize();

    gs.dealerLogic(dealer);

    CHECK(dealer.getHand().handSize() == initialSize);  // non ha pescato
    CHECK(dealer.getHand().handScore() == 17);      // rimane invariato
    CHECK(dealer.isStanding() == true);
  }

  SUBCASE("Dealer parte sopra 17: non deve pescare") {
    dealer.getHand() =
        Hand(Card("Hearts", "10", 10), Card("Spades", "9", 9));  // 19
    int initialSize = dealer.getHand().handSize();

    gs.dealerLogic(dealer);

    CHECK(dealer.getHand().handSize() == initialSize);  // non ha pescato
    CHECK(dealer.getHand().handScore() == 19);      // rimane invariato
    CHECK(dealer.isStanding() == true);
  }
   SUBCASE("Soft 16 (A+5): deve pescare") {
        dealer.getHand() = Hand(Card("Hearts", "A", 11), Card("Spades", "5", 5));
        gs.dealerLogic(dealer);

        CHECK(dealer.getHand().handScore() >= 17);
        CHECK(dealer.isStanding() == true);
    }

    SUBCASE("Soft 17 (A+6): deve stare") {
        dealer.getHand() = Hand(Card("Hearts", "A", 11), Card("Spades", "6", 6));
        int initialSize = dealer.getHand().handSize();

        gs.dealerLogic(dealer);

        CHECK(dealer.getHand().handSize() == initialSize); // non ha pescato
        CHECK(dealer.getHand().handScore() == 17);
        CHECK(dealer.isStanding() == true);
    }
}
 }
