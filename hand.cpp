#include "hand.hpp"

#include <numeric>

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

int Hand::hand_score() {
  int score = std::accumulate(
      hand_.begin(), hand_.end(), 0,
      [](int acc, Card card) { return acc + card.game_value_; });
}

void Hand::hand_draw(Deck &deck) {
  Card top = deck.topCard();
  hand_.emplace_back(top);
  if (hand_score() > 21) {
    for (auto it = hand_.begin(); it != hand_.end(); ++it) {
      if (it->range_ == "A") {
        it->game_value_ = 1;
        break;
      }
    }
  }
}

void Hand::hand_covered_draw(Deck &deck) {
  Card top = deck.topCard();
  hand_.emplace_back(top);
  top.face_ = false;
  if (hand_score() > 21)  // se sfori dai 21 controlla se ci sono degli assi,
                          // assegna al primo
  {                       // che trovi il valore 1 e esci dal ciclo
    for (auto it{hand_.begin()}; it != hand_.end(); ++it) {
      if (it->range_ == "A") {
        it->game_value_ = 1;
        break;
      }
    }
  }
}

void Hand::card_reveal() {
  for (auto it = hand_.begin(); it != hand_.end(); ++it) {
    if (it->face_ == false) {
      it->face_ = true;
    }
  }
}
}  // namespace el