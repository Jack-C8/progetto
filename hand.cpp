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
    throw std::runtime_error{"You can't hit, your score is the highest possible"};
  }
  Card top = deck.topCard();
  hand_.emplace_back(top);
}
Card Hand::hand_element(int number) const { return hand_[number]; }

void Hand::add_card(const Card& c) {
  if (hand_score() >= 21) {
    throw std::runtime_error{"You can't hit, your score is the highest possible"};
  }

  hand_.push_back(c);
}

void Hand::remove_card() { hand_.pop_back(); }

bool Hand::cansplit() {
  if (hand_.size() == 2 && hand_[0].range_ == hand_[1].range_) {
    return true;
  } else {
    return false;
  }
}

Hand split(Hand& original, Deck& deck) {
  if (original.cansplit() == false) {
    throw std::runtime_error{"You can't split these cards!"};
  }

  const Card c1 = original.hand_element(0);
  const Card c2 = original.hand_element(1);

  Hand splitted;
  splitted.add_card(c2);
  original.remove_card();

  splitted.hand_draw(deck);
  original.hand_draw(deck);

  return splitted;
}

bool blackjack(Hand& player_hand) {
  if (player_hand.hand_size() == 2 && player_hand.hand_score() == 21) {
    return true;
  } else {
    return false;
  }
}
}