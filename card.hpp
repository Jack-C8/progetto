#ifndef EL_CARD_HPP
#define EL_CARD_HPP

namespace el {

struct Card {
  std::string suit;
  std::string range;
  int game_value;
  bool face;

  Card(const std::string &suit, const std::string &range, int const game_value,
       bool const face);
};

bool operator==(const Card &one, const Card &other);

class Deck {
  std::vector<Card> deck;

 public:
  Deck();

  void shuffle();

  Card topCard();

  size_t deck_size() const;

  const std::vector<Card> &get_deck() const;
};
}  // namespace el
#endif