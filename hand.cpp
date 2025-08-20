#include "hand.hpp"

#include "card.hpp"

namespace el {

Hand::Hand(Card c1, Card c2) {
  hand_.push_back(c1);
  hand_.push_back(c2);
}

Hand::Hand() {};
// secondo costruttore nullo su richiesta.

const Card Hand::hand_element(int i) const { return hand_[i]; }

int Hand::hand_size() { return static_cast<int>(hand_.size()); }

int Hand::hand_score() const {
  int score = std::accumulate(
      hand_.begin(), hand_.end(), 0,
      [](int acc, Card card) { return acc + card.game_value_; });

  // fin qui calcolo con gli assi a valore uguale ad 11.
  // aggiungo il metodo di ricalcolo per gli assi, in questa versione non
  // cambiamo elementi della carta ma solo score!

  int aces = 0;
  for (const auto& card : hand_) {
    if (card.range_ == "A") {
      ++aces;
    }
  }

  while (score > 21 && aces > 0) {
    score -= 10;
    --aces;
  }
  return score;
}

void Hand::hand_draw(Deck& deck) {
  Card top = deck.topCard();
  hand_.emplace_back(top);
}

bool Hand::splittable_hand() {
  if (hand_.size() == 2 && hand_[0].range_ == hand_[1].range_) {
    return true;
  } else {
    return false;
  }
}
}  // namespace el