#include "doctest.h"
#include "card.cpp"

TEST_CASE("Deck shuffle") {
  el::Deck deck1;
  el::Deck deck2;

  SUBCASE("Two shuffled decks") {
    deck1.shuffle();
    deck2.shuffle();
    // mescolo i mazzi e con sto ciclo che almeno in una posizione le carte sono
    // diverse il che vuol dire che i mazzi sono stati mischiati.
    // iteratore arriva fino a 52 perché se trova un mazzo in ordine è già un
    // problema.
    bool different = false;
    for (size_t i{0}; i < 52; ++i) {
      if (!(deck1.get_deck()[i] == deck2.get_deck()[i])) {
        different = true;
        break;
      }
    }
    CHECK(different == true);
  }
  SUBCASE("One shuffled deck & one unshuffled deck") {
    deck2.shuffle();
    bool different = false;
    for (size_t i{0}; i < 14; ++i) {
      if (!(deck1.get_deck()[i] == deck2.get_deck()[i])) {
        different = true;
        break;
      }
    }
    CHECK(different == true);
  }
  SUBCASE("Number of cards after shuffle") {
    deck1.shuffle();
    CHECK(deck1.deck_size() == 156);
  }
  SUBCASE("Card operator==") {
    el::Card c1{"Hearts", "2", 2};
    el::Card c2{"Hearts", "3", 3};
    el::Card c3{"Clubs", "2", 2};
    el::Card c4{"Hearts", "2", 3};
    CHECK((c1 == c1) == true);
    CHECK((c1 == c2) == false);
    CHECK((c1 == c3) == false);
    CHECK((c1 == c4) == true); // operator== non deve tener conto del game_value della carta
  }
}