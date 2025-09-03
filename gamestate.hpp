#ifndef EL_GAMESTATE_HPP
#define EL_GAMESTATE_HPP

#include <vector>

#include "card.hpp"
#include "hand.hpp"
#include "player.hpp"

namespace el {

class GameState {
 public:
  Deck deck_;
  std::vector<Player> players_;
  int current_turn{0};
  bool round_over{false};
  float humanStartingFishes_;
  float humanGameBet_;

 public:
  GameState(float humanStartingFishes, float humanGameBet);

  void startGame(float humanFishes, float humanBet);

  void nextTurn();

  void advanceTurn();

  void botLogic1(Player& bot1, Hand& dealerHand);

  void botLogic2(Player& bot2, Hand& dealerHand);

  void dealerLogic(Player& player);
};

void payout(GameState& state);

};  // namespace el

#endif