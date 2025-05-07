#include "card.hpp"

#include <algorithm>
#include <random>
#include <stdexcept>
#include <string>

namespace el {

Deck::Deck() {
  std::string suits[] = {"Hearts", "Clubs", "Spades", "Diamonds"};
  std::string ranges[] = {"2", "3",  "4", "5", "6", "7", "8",
                          "9", "10", "J", "Q", "K", "A"};
  int game_value[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

  for (int n = 0; n < 3; ++n) {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 13; ++j) {
        deck.emplace_back(suits[i], ranges[j], game_value[j]);
      }
    }
  }
}

void Deck::shuffle() {
  std::random_device rd;
  std::default_random_engine rng(rd());
  std::shuffle(deck.begin(), deck.end(), rng);
}

Card Deck::topCard() {
  if (deck.size() < 30) {
    throw std::runtime_error{"Not enough cards, reset the game!"};
  }
  Card top = deck.back();
  deck.pop_back();
  return top;
}

size_t Deck::deck_size() const { return deck.size(); }

const std::vector<Card>& Deck::get_deck() const { return deck; }

}  // namespace el

/*per deck.back chiedere se c'è bisogno della dereferenzazzione dell'ultimo
 * elemento di deck per associarlo a top*/