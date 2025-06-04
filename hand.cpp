#include <numeric>

#include "hand.hpp"
#include "card.hpp"

namespace el {

Hand::Hand(Card c1, Card c2) {
  hand_.push_back(c1);
  hand_.push_back(c2);
}

Hand::Hand() {}
// secondo costruttore nullo su richiesta.
const Card Hand::element(int i) const { return hand_[static_cast<int>(i)]; }

int Hand::size() { return static_cast<int>(hand_.size()); }

int Hand::score() {
  int score = std::accumulate(
      hand_.begin(), hand_.end(), 0,
      [](int acc, Card card) { return acc + card.game_value_; });
  return score;
}

void Hand::hand_draw(Deck &deck) {
  Card top = deck.topCard();
  hand_.emplace_back(top);
  if (score() > 21) {
    for (auto it = hand_.begin(); it != hand_.end(); ++it) {
      if (it->range_ == "A") {
        it->game_value_ = 1;
        break;
      }
    }
  }
}
}  // namespace el