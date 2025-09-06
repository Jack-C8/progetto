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

  Hand(Card c1, Card c2);

  int handSize();

  int handScore() const;

  void handDraw(el::Deck& deck);

  Card handElement(std::size_t number) const;

  void addCard(const Card& c);

  void removeCard();

  bool blackjack();
};
}  // namespace el
#endif