#ifndef EL_GAME_STATE_HPP
#define EL_GAME_STATE_HPP

#include <vector>

#include "card.hpp"
#include "hand.hpp"
#include "player.hpp"

namespace el {

class GameState {
  private:
  Deck deck_;
  std::vector<Player> players_;
  bool roundOver{false};
  float humanStartingFishes_;
  float humanGameBet_;
  bool dealerCardShown{false};

  public:
  int currentTurn{0};

  GameState(float humanStartingFishes, float humanGameBet);

  void startGame(float humanFishes, float humanBet);

  void nextTurn();

  void advanceTurn();

  void botLogic1(Player& bot1, const Hand& dealerHand);

  void botLogic2(Player& bot2, const Hand& dealerHand);

  void dealerLogic(Player& player);

  std::vector<Player>& getPlayers() { return players_; }


};

void payOut(GameState& state);

};  // namespace el

#endif