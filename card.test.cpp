#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "card.hpp"

TEST_CASE("Deck shuffle") {
    element::Deck deck1;
    element::Deck deck2;
  
    SUBCASE("Shuffled Deck") {
      deck1.shuffle();
      deck2.shuffle();
  
      bool different = false;
      for (size_t i = 0; i < 52; ++i) {
        if (!(deck1.getCards()[i] == deck2.getCards()[i])) {
          different = true;
          break;
        }
      }
  
      CHECK(different == true);
    }
    SUBCASE("Number of cards after shuffle") {
      deck1.shuffle();
      CHECK(deck1.getNumberOfCards() == 52);
    }
  }