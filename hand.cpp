#include "hand.hpp"

#include "card.hpp"

namespace el {

Hand::Hand(const Card c1, const Card c2) {
  hand_.push_back(c1);
  hand_.push_back(c2);
}

Hand::Hand() {}

int Hand::hand_size() { return static_cast<int>(hand_.size()); }

int Hand::hand_score() const {
  int score = std::accumulate(
      hand_.begin(), hand_.end(), 0,
      [](int acc, Card card) { return acc + card.game_value_; });

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
  if (hand_score() >= 21) {
    throw std::runtime_error{
        "You can't hit, your score is the highest possible"};
  }
  Card top = deck.topCard();
  hand_.emplace_back(top);
}
Card Hand::hand_element(int number) const { return hand_[number]; }

void Hand::add_card(const Card& c) {
  if (hand_score() >= 21) {
    throw std::runtime_error{
        "You can't hit, your score is the highest possible"};
  }

  hand_.push_back(c);
}

void Hand::remove_card() { hand_.pop_back(); }

bool Hand::blackjack() {
  if (hand_size() == 2 && hand_score() == 21) {
    return true;
  } else {
    return false;
  }
}
}  // namespace el