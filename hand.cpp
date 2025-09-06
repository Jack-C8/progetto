#include "hand.hpp"

namespace el {
Hand::Hand(Card c1, Card c2) {
  hand_.emplace_back(c1);
  hand_.emplace_back(c2);
}

Hand::Hand() {}

int Hand::handSize() { return static_cast<int>(hand_.size()); }

int Hand::handScore() const {
  int score = std::accumulate(
      hand_.begin(), hand_.end(), 0,
      [](int acc, Card card) { return acc + card.getGameValue(); });

  int aces = 0;
  for (Card card : hand_) {
    if (card.getRange() == "A") {
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
Card Hand::handElement(std::size_t number) const { return hand_[number]; }

void Hand::addCard(const Card& c) {
  if (handScore() >= 21) {
    throw std::runtime_error{
        "You can't hit, your score is the highest possible"};
  }

  hand_.emplace_back(c);
}

void Hand::removeCard() { hand_.pop_back(); }

bool Hand::blackjack() {
  if (handSize() == 2 && handScore() == 21) {
    return true;
  } else {
    return false;
  }
}
}  // namespace el