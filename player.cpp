#include "player.hpp"

#include "card.hpp"
#include "hand.hpp"

namespace el {

Player::Player(PlayerType type, float fishes, float bet)
    : type_(type), fishes_(fishes), bet_(bet) {}

void Player::hit(Deck& deck) { hand_.hand_draw(deck); }

void Player::stand() { standing_ = true; }

void Player::double_down(Deck& deck) {
  if (fishes_ >= bet_) {
    hit(deck);
    fishes_ -= bet_;
    bet_ *= 2;
    standing_ = true;
  } else {
    throw std::runtime_error{"You can't double down!"};
  }
}

};  // namespace el