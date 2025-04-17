#ifndef EL_CARD_HPP
#define EL_CARD_HPP
#include <string>
#include <vector>

namespace el {

struct Card {
  std::string suit;
  std::string range;
  int game_value;
  bool face;

  Card(const std::string& suit, const std::string& range, int game_value,
       bool face = true)
      : suit{suit}, range{range}, game_value{game_value}, face{face} {}
};

class Deck {
  std::vector<Card> deck;

 public:
  Deck();

  void shuffle();

  Card topCard();
  size_t deck_size() const;
  const std::vector<Card>& get_deck() const;
};
}  // namespace el
#endif
