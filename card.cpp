#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <algorithm>
#include <random>
#include <string>
#include <vector>

#include "doctest.h"

// definition of card through a struct, easier and more efficient than a class

struct Card {
  std::string suit_;
  std::string range_;
  int game_value_;
  Card(const std::string& suit, const std::string& range, int game_value) : suit_{suit}, range_{range}, game_value_{game_value} {}

  bool operator==(const Card& other) const {
    return suit_ == other.suit_ && range_ == other.range_;
  }
};
class Deck {
  std::vector<Card> cards;

 public:
  // deck constructor with for-loop to create starting deck
  Deck() {
    std::string suits[] = {"Hearts", "Clubs", "Spades", "Diamonds"};
    std::string ranges[] = {"2", "3",  "4", "5", "6", "7", "8",
                            "9", "10", "J", "Q", "K", "A"};
    int game_value[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
    // std::string suits[] is not a lambda but contains the possible value in
    // order.

    for (int i = 0; i < 3; ++i) {
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

int main() {
  Card c{"spade", "3", 3};
  std::cout << c.suit_;
}