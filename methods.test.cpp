#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "methods.hpp"

#include "card.hpp"
#include "doctest.h"
#include "hand.hpp"

TEST_CASE("Testing methods and main") {
  el::GameState state;
  el::Deck deck;
  el::Hand dealer(deck.topCard(), deck.topCard());
  el::dealer(deck, dealer);

  SUBCASE("Gamestate Constructor") {
    CHECK(state.your_hand.hand_size() == 2);
    CHECK(state.bot1_hand.hand_size() == 2);
    CHECK(state.bot2_hand.hand_size() == 2);
    CHECK(state.dealer_hand.hand_size() == 2);
    CHECK(state.deck.size() == 52 - 8);
    CHECK(state.your_score == state.your_hand.hand_score());
  }
  SUBCASE("Players") {
    deck.shuffle();
    el::Hand dealer(deck.topCard(), deck.topCard());
    el::dealer(deck, dealer);
    el::Hand bot1(deck.topCard(), deck.topCard());
    el::bot1(deck, bot1);
    el::Hand bot2(deck.topCard(), deck.topCard());
    el::bot1(deck, bot2);
    CHECK(dealer.hand_score() >= 17);
    CHECK(bot1.hand_score() >= 17);
    CHECK(bot2.hand_score() >= 18);
  }
}