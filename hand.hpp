#ifndef EL_HAND_HPP
#define EL_HAND_HPP

#include <numeric>
#include <stdexcept>
#include <vector>

#include "card.hpp"

namespace el {

class Hand {
  std::vector<Card> hand_{};

 public:
  Hand();

  Hand(const Card c1, const Card c2);

  int hand_size();

  int hand_score() const;

  void hand_draw(el::Deck& deck);

  Card hand_element(std::size_t number) const;

  void add_card(const Card& c);

  void remove_card();

  bool blackjack();
};
}  // namespace el
#endif