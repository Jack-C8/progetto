#include "hand.hpp"

#include <numeric>

#include "card.hpp"

// mettere i trattini sotto

namespace el {

Hand::Hand(Card c1, Card c2) {
  hand_.push_back(c1);
  hand_.push_back(c2);
}

int Hand::size() { return static_cast<int>(hand_.size()); }

const Card Hand::element(int i) const { return hand_[i + 1]; }

int Hand::score() {
  int score = std::accumulate(
      hand_.begin(), hand_.end(), 0,
      [](int acc, el::Card card) { return acc + card.game_value_; });

  return score;
}

void Hand::Draw(Deck &deck) {
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

void Hand::covered_Draw(Deck &deck) {
  Card top = deck.topCard();
  hand_.emplace_back(top);
  top.face_ = false;
  if (score() > 21)  // se sfori dai 21 controlla se ci sono degli assi,
                     // assegna al primo
  {                  // che trovi il valore 1 e esci dal ciclo
    for (auto it{hand_.begin()}; it != hand_.end(); ++it) {
      if (it->range_ == "A") {
        it->game_value_ = 1;
        break;
      }
    }
  }
}

void Hand::reveal() {
  for (auto it = hand_.begin(); it != hand_.end(); ++it) {
    if (it->face_ == false) {
      it->face_ = true;
    }
  }
}

std::vector<el::Card> Hand::hand() const { return hand_; }
}