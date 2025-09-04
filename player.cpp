#include "player.hpp"

#include "card.hpp"
#include "hand.hpp"

namespace el {

Player::Player(PlayerType type, float fishes, float bet)
    : type_(type), fishes_(fishes), bet_(bet) {}

void Player::hit(Deck& deck) { hand_.handDraw(deck); }

void Player::stand() { standing_ = true; }

void Player::doubleDown(Deck& deck) {
  if (fishes_ >= bet_) {
    hit(deck);
    fishes_ -= bet_;
    bet_ *= 2;
    standing_ = true;
  } else {
    throw std::runtime_error{"You can't double down!"};
  }
}

PlayerType Player::getType() const { return type_; }

float& Player::getFishes() { return fishes_; }

float& Player::getBet() { return bet_; }

Hand& Player::getHand() { return hand_; }

bool& Player::isStanding() { return standing_; }

};  // namespace el