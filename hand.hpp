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

  int handSize() const;

  int handScore() const;

  void handDraw(el::Deck& deck);

  Card handElement(unsigned int& number) const;

  void addCard(Card& c);

  void removeCard();

  bool blackjack() const;
};
}  // namespace el
#endif