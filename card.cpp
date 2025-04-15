#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <algorithm>
#include <random>
#include <string>
#include <vector>

#include "doctest.h"

// definition of card through a struct, easier and more efficient than a class

struct Card {
  std::string suit;
  std::string range;
  int game_value;
  // nuovo operatore per confronto di carte!
  Card(const std::string& suit, const std::string& range, int game_value) {
    this->suit = suit;
    this->range = range;
    this->game_value = game_value;
}

  bool operator==(const Card& other) const {
    return suit == other.suit && range == other.range;
  }
};
class Deck {
  std::vector<Card> cards;

 public:
  // deck constructor with for-loop for create starting deck
  Deck() {
    std::string suits[] = {"Hearts", "Clubs", "Spades", "Diamonds"};
    std::string ranges[] = {"2", "3",  "4", "5", "6", "7", "8",
                            "9", "10", "J", "Q", "K", "A"};
    int game_value[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
    // std::string suits[] is not a lambda but contains the possible value in
    // order.

    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 13; ++j) {
        cards.emplace_back(suits[i], ranges[j], game_value[j]);
      }
    }
  }
  // shuffle method because constructor create it in order
  void shuffle() {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(cards.begin(), cards.end(), rng);
  }

  size_t getNumberOfCards() const { return cards.size(); }
  const std::vector<Card>& getCards() const { return cards; }
};

/*Test da implementare: verifica della size di cards,
verificare che il mazzo abbia tutte le carte in modo corretto,
verificare che il mescolamento funzioni e che il mazzo cambi ordine,
verificare che i valori siano quelli giusti*/

TEST_CASE("Deck shuffle") {
  Deck deck1;
  Deck deck2;

  SUBCASE("Shuffled Deck") {
    deck1.shuffle();
    deck2.shuffle();

    // mescolo i mazzi e con sto ciclo che almeno in una posizione le carte sono
    // diverse il che vuol dire che i mazzi sono stati mischiati.
    // iteratore arriva fino a 52 perché se trova un mazzo in ordine è già un
    // problema.

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