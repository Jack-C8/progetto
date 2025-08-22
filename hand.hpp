#ifndef El_HAND_HPP
#define EL_HAND_HPP

#include <numeric>
#include <vector>
#include <stdexcept>

#include "card.hpp"

namespace el {

class Hand {
  std::vector<Card> hand_{};

 public:
  Hand();

  Hand(const Card c1, const Card c2);

  const Card element(int i) const;

  int hand_size();

  int hand_score() const;

  void hand_draw(el::Deck& deck);

  Card hand_element(int number) const;

  void add_card(const Card& c);

  void remove_card();

  bool cansplit();
};
Hand split(Hand& original, Deck& deck);

bool blackjack(Hand& player_hand);

} 
#endif