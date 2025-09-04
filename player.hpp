#ifndef EL_PLAYER_HPP
#define EL_PLAYER_HPP

#include <stdexcept>
#include <vector>

#include "card.hpp"
#include "hand.hpp"

namespace el {
enum class PlayerType { Human, Bot1, Bot2, Dealer };

class Player {
 private:
  PlayerType type_;
  Hand hand_;
  float fishes_;
  float bet_;
  bool standing_{false};
  

 public:
  Player(PlayerType type, float fishes, float bet);

  void hit(Deck& deck);

  void stand();

  void doubleDown(Deck& deck);

  PlayerType getType() const;

  float& getFishes();

  float& getBet();

  Hand& getHand();

  bool& isStanding();
};

}  // namespace el
#endif