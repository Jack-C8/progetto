#include "hand.hpp"

#include "card.hpp"

namespace el {

Hand::Hand(const Card c1, const Card c2) {
  hand_.push_back(c1);
  hand_.push_back(c2);
}

Hand::Hand() {}

int Hand::handSize() const { return static_cast<int>(hand_.size()); }

int Hand::handScore() const {
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

void Hand::handDraw(Deck& deck) {
  if (handScore() >= 21) {
    throw std::runtime_error{
        "You can't hit, your score is the highest possible"};
  }
  Card top = deck.topCard();
  hand_.emplace_back(top);
}
Card Hand::handElement(unsigned int& number) const { return hand_[number]; }

void Hand::addCard(Card& c) {
  if (handScore() >= 21) {
    throw std::runtime_error{
        "You can't hit, your score is the highest possible"};
  }

  hand_.push_back(c);
}

void Hand::removeCard() { hand_.pop_back(); }

bool Hand::blackjack() const {
  if (handSize() == 2 && handScore() == 21) {
    return true;
  } else {
    return false;
  }
}

}  