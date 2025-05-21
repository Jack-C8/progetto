#ifndef HD_HAND_HPP
#define HD_HAND_HPP

#include <vector>

#include "card.hpp"

namespace el {

class Hand {
  std::vector<Card> hand_{};

 public:
  Hand(Card c1, Card c2);
  Hand();

  const Card hand_element(int i) const;

  int hand_size();

  int hand_score();

  void hand_draw(el::Deck &deck);

  void hand_covered_draw(el::Deck &deck);

  void card_reveal();

  std::vector<el::Card> hand() const;
};
}  // namespace el
#endif