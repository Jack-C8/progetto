#ifndef EL_PLAYER_HPP
#define EL_PLAYER_HPP

#include <stdexcept>
#include <vector>

#include "card.hpp"
#include "hand.hpp"

namespace el {
enum class PlayerType { Human, Bot1, Bot2, Dealer };

class Player {
  public:
  PlayerType type_;
  Hand hand_;
  float fishes_;
  float bet_;
  bool standing_{false}; //not private because we want access to them.


  Player(PlayerType type, float fishes, float bet);

  void hit(Deck& deck);

  void stand();

  void double_down(Deck& deck);
};

}  // namespace el
#endif