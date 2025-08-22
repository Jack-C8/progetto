#ifndef El_HAND_HPP
#define EL_HAND_HPP

#include <vector>
#include <numeric>
#include "card.hpp"

namespace el {

class Hand {
  std::vector<Card> hand_{};

 public:
  Hand(Card c1, Card c2);
  Hand();

  const Card element(int i) const;

  int size();

  int hand_score() const;

  void hand_draw(el::Deck &deck);

  bool splittable_hand();
};
}
#endif